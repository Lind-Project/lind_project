#!/usr/bin/env bash
set -euo pipefail

# lmbench WASM build helper for lind-wasm-apps
#
# High level:
#   1) Reuse the merged `libc.a` augmentation unless its inputs changed.
#   2) Rebuild lmbench only when the toolchain or build inputs changed.
#   3) Stage final artifacts under build/lmbench/bin.
#   4) Require cwasm generation for the staged executables and copy the
#      resulting .cwasm files back onto the final extensionless program names.
#
# Dynamic loading support:
#   Set LIND_DYLINK=1 to build lmbench as position-independent executables
#   for the dylink branch. This adds -fPIC to CFLAGS, uses PIE link flags,
#   and applies the dylink-aware wasm-opt passes.

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"

if [[ -z "${LIND_WASM_ROOT:-}" ]]; then
  LIND_WASM_ROOT="$(cd "$REPO_ROOT/.." && pwd)"
fi

APPS_BUILD="$REPO_ROOT/build"
APPS_OVERLAY="$APPS_BUILD/sysroot_overlay"
MERGED_SYSROOT="$APPS_BUILD/sysroot_merged"
APPS_LMBENCH_CANON_ROOT="$APPS_BUILD/lmbench"
TOOL_ENV="$APPS_BUILD/.toolchain.env"
MAX_WASM_MEMORY="${MAX_WASM_MEMORY:-67108864}"
ENABLE_WASI_THREADS="${ENABLE_WASI_THREADS:-1}"
WASM_OPT="${WASM_OPT:-$LIND_WASM_ROOT/tools/binaryen/bin/wasm-opt}"
LIND_BOOT="${LIND_BOOT:-$LIND_WASM_ROOT/build/lind-boot}"
JOBS="${JOBS:-$(nproc 2>/dev/null || getconf _NPROCESSORS_ONLN || echo 4)}"
##################
# These flags expose the scratch-rebuild tradeoff directly at the script layer.
# lmbench's staged executables now always require the full cwasm-backed output
# set mandated by issue #127, regardless of artifact mode.
##################
LIND_DYLINK="${LIND_DYLINK:-0}"
ARTIFACT_MODE="${ARTIFACT_MODE:-fast}"
FORCE_CLEAN="${FORCE_CLEAN:-0}"
FORCE_CONFIGURE="${FORCE_CONFIGURE:-0}"
CACHE_REVISION="2"
STATE_DIR="$APPS_BUILD/.lmbench_state"
LIBC_SIG_FILE="$STATE_DIR/libc.sig"
BUILD_SIG_FILE="$STATE_DIR/build.sig"
COMB_DIR="$APPS_BUILD/.lmbench_libc_objs"
##################
# The state directory stores signatures for the two expensive phases in this
# script: rebuilding the combined libc archive and deciding whether a clean
# lmbench rebuild is actually necessary. Without that, repeated invocations
# pay the same cost even when the inputs are unchanged.
##################
mkdir -p "$STATE_DIR"

if [[ -r "$TOOL_ENV" ]]; then
  # shellcheck disable=SC1090
  . "$TOOL_ENV"
else
  echo "[lmbench] ERROR: missing toolchain env '$TOOL_ENV' (run 'make preflight' first)" >&2
  exit 1
fi

: "${CLANG:?missing CLANG in $TOOL_ENV}"
: "${AR:?missing AR in $TOOL_ENV}"
: "${RANLIB:?missing RANLIB in $TOOL_ENV}"

##################
# These helpers exist for two different reasons: hashing makes the cache
# decisions deterministic, and the bounded-background helpers let the optional
# post-processing loops run concurrently without spawning an unbounded number
# of `wasm-opt` or `lind-boot` jobs.
##################
supports_cflag() {
  local flag="$1"
  printf 'int main(void){return 0;}\n' | \
    "$CLANG" --target=wasm32-unknown-wasi --sysroot="$MERGED_SYSROOT" \
    $flag -x c -c -o /dev/null - >/dev/null 2>&1
}

hash_file() {
  local path="$1"
  if [[ -e "$path" ]]; then
    sha256sum "$path" | awk '{print $1}'
  else
    echo "missing"
  fi
}

list_hashes() {
  local item
  for item in "$@"; do
    if [[ -e "$item" ]]; then
      printf '%s %s\n' "$(sha256sum "$item" | awk '{print $1}')" "$item"
    else
      printf 'missing %s\n' "$item"
    fi
  done
}

run_limited() {
  local limit="$1"
  shift
  while (( $(jobs -rp | wc -l) >= limit )); do
    wait -n || true
  done
  "$@" &
}

wait_for_background_jobs() {
  local rc=0
  while [[ -n "$(jobs -rp)" ]]; do
    if ! wait -n; then
      rc=1
    fi
  done
  return "$rc"
}

run_wasm_opt_replace() {
  local src="$1"
  local raw="$2"
  local out="$3"
  local tmp="${out}.tmp"
  cp "$src" "$raw"
  if [[ "$LIND_DYLINK" == "1" ]]; then
    # dylink-aware wasm-opt: epoch-import and asyncify-import-globals
    # are needed because epoch counter and asyncify globals live in the
    # host (libc module), not in the main module.
    if "$WASM_OPT" \
        --fpcast-emu \
        --enable-bulk-memory --enable-threads \
        --epoch-injection --pass-arg=epoch-import --pass-arg=epoch-main-module \
        --asyncify --pass-arg=asyncify-import-globals \
        -O2 --debuginfo \
        "$raw" -o "$tmp"; then
      mv "$tmp" "$out"
    else
      rm -f "$tmp"
      return 1
    fi
  else
    if "$WASM_OPT" --fpcast-emu --epoch-injection --asyncify --debuginfo -O2 "$raw" -o "$tmp"; then
      mv "$tmp" "$out"
    else
      rm -f "$tmp"
      return 1
    fi
  fi
}

BASE_LIBC="$MERGED_SYSROOT/lib/wasm32-wasi/libc.a"
TIRPC_MERGE_DIR="$APPS_OVERLAY/usr/lib/wasm32-wasi/merge_tmp"

if [[ ! -f "$BASE_LIBC" ]]; then
  echo "[lmbench] ERROR: merged sysroot libc.a not found at: $BASE_LIBC" >&2
  echo "[lmbench] Hint: run 'make merge-sysroot' before 'make lmbench'." >&2
  exit 1
fi

##################
# For static builds, lmbench needs a libc archive that includes the libtirpc
# objects. For dylink builds, libtirpc.so is loaded separately at runtime.
##################
if [[ "$LIND_DYLINK" != "1" ]]; then
  if [[ ! -d "$TIRPC_MERGE_DIR" ]]; then
    echo "[lmbench] ERROR: expected libtirpc .o dir '$TIRPC_MERGE_DIR' not found" >&2
    echo "[lmbench] Hint: did 'make libtirpc' succeed?" >&2
    exit 1
  fi

  shopt -s nullglob
  tirpc_objs=("$TIRPC_MERGE_DIR"/*.o)
  shopt -u nullglob

  if (( ${#tirpc_objs[@]} == 0 )); then
    echo "[lmbench] ERROR: no libtirpc .o files under $TIRPC_MERGE_DIR" >&2
    exit 1
  fi

  libc_signature() {
    {
      echo "rev=$CACHE_REVISION"
      echo "base=$(hash_file "$BASE_LIBC")"
      echo "ar=$AR"
      echo "ranlib=$RANLIB"
      list_hashes "${tirpc_objs[@]}"
    } | sha256sum | awk '{print $1}'
  }
else
  echo "[lmbench] dylink mode: skipping tirpc merge (libtirpc.so loaded at runtime)"
fi

LM_BENCH_BIN_DIR="$REPO_ROOT/lmbench/bin/wasm32-wasi"
mkdir -p "$LM_BENCH_BIN_DIR"

REAL_CC="$CLANG --target=wasm32-unknown-wasi --sysroot=$MERGED_SYSROOT"
CFLAGS="-DNO_PORTMAPPER -O2 -g -I$MERGED_SYSROOT/include -I$MERGED_SYSROOT/include/wasm32-wasi -I$MERGED_SYSROOT/include/tirpc"

if [[ "$LIND_DYLINK" == "1" ]]; then
  echo "[lmbench] Dynamic linking mode enabled (LIND_DYLINK=1)"
  CFLAGS+=" -fPIC"
  # add-export-tool is used after linking to export relocation and stack symbols
  ADD_EXPORT_TOOL="$LIND_WASM_ROOT/tools/add-export-tool/add-export-tool"
  if [[ ! -x "$ADD_EXPORT_TOOL" ]]; then
    echo "[lmbench] ERROR: add-export-tool not found at '$ADD_EXPORT_TOOL'" >&2
    exit 1
  fi
  # Extra objects required for dynamic PIE executables
  DYLINK_CRT_OBJS=(
    "$MERGED_SYSROOT/lib/wasm32-wasi/crt1_shared.o"
    "$MERGED_SYSROOT/lib/wasm32-wasi/lind_utils.o"
  )
  for obj in "${DYLINK_CRT_OBJS[@]}"; do
    if [[ ! -f "$obj" ]]; then
      echo "[lmbench] ERROR: required dylink CRT object '$obj' not found." >&2
      echo "[lmbench] Hint: rebuild sysroot on the dylink branch (make sysroot in lind-wasm)." >&2
      exit 1
    fi
  done
  LDFLAGS_WASM=(
    "-nostartfiles"
    "-Wl,-pie"
    "-Wl,--import-table"
    "-Wl,--import-memory"
    "-Wl,--export-memory"
    "-Wl,--max-memory=${MAX_WASM_MEMORY}"
    "-Wl,--allow-undefined"
    "-Wl,--unresolved-symbols=import-dynamic"
    "-Wl,--export=__wasm_call_ctors"
    "-Wl,--export-if-defined=__wasm_init_tls"
    "-Wl,--export=__tls_base"
    "-L$MERGED_SYSROOT/lib/wasm32-wasi"
    "-L$MERGED_SYSROOT/usr/lib/wasm32-wasi"
    "${DYLINK_CRT_OBJS[@]}"
  )
else
  LDFLAGS_WASM=(
    "-Wl,--import-memory,--export-memory,--max-memory=${MAX_WASM_MEMORY},--export=__stack_pointer,--export=__stack_low,--export=__tls_base"
    "-L$MERGED_SYSROOT/lib/wasm32-wasi"
    "-L$MERGED_SYSROOT/usr/lib/wasm32-wasi"
  )
fi

if [[ "$ENABLE_WASI_THREADS" == "1" ]]; then
  thread_flag="-mthread-model=posix"
  if ! supports_cflag "$thread_flag"; then
    thread_flag=""
  fi
  if supports_cflag "-pthread" && supports_cflag "-matomics" && supports_cflag "-mbulk-memory"; then
    CFLAGS+=" -pthread -matomics -mbulk-memory"
    if [[ -n "$thread_flag" ]]; then
      CFLAGS+=" $thread_flag"
    else
      echo "[lmbench] WARNING: clang does not support -mthread-model=posix; skipping thread model flag."
    fi
    LDFLAGS_WASM+=("-Wl,--shared-memory")
  else
    echo "[lmbench] WARNING: clang does not support wasi-threads flags; disabling shared memory."
    ENABLE_WASI_THREADS="0"
  fi
fi

LDFLAGS="${LDFLAGS_WASM[*]}"
if [[ "$LIND_DYLINK" == "1" ]]; then
  # In dylink mode, tirpc symbols come from libtirpc.so loaded at runtime
  LDLIBS="-lm"
else
  LDLIBS="-ltirpc -lm"
fi

##################
# The compile step has its own signature because a clean rebuild only makes
# sense when the toolchain, memory/threading configuration, or lmbench make
# inputs changed. This keeps the script from doing `make clean` on every run.
##################
build_signature() {
  {
    echo "rev=$CACHE_REVISION"
    echo "makefile=$(hash_file "$REPO_ROOT/lmbench/src/Makefile")"
    echo "clang=$CLANG"
    echo "merged=$MERGED_SYSROOT"
    echo "memory=$MAX_WASM_MEMORY"
    echo "threads=$ENABLE_WASI_THREADS"
    echo "dylink=$LIND_DYLINK"
    echo "cflags=$CFLAGS"
    echo "ldflags=$LDFLAGS"
    echo "ldlibs=$LDLIBS"
  } | sha256sum | awk '{print $1}'
}

##################
# For static builds only: create combined libc.a with tirpc objects merged in.
# For dylink builds, libtirpc.so is loaded separately at runtime.
##################
if [[ "$LIND_DYLINK" != "1" ]]; then
  mkdir -p "$APPS_BUILD/lib"
  COMBINED_LIBC="$APPS_BUILD/lib/libc.a"
  current_libc_sig="$(libc_signature)"

  if [[ "$FORCE_CLEAN" == "1" || "$FORCE_CONFIGURE" == "1" || ! -f "$LIBC_SIG_FILE" || "$(cat "$LIBC_SIG_FILE" 2>/dev/null || true)" != "$current_libc_sig" || ! -f "$COMBINED_LIBC" ]]; then
    rm -rf "$COMB_DIR"
    mkdir -p "$COMB_DIR"

    echo "[lmbench] extracting base libc objects..."
    (
      cd "$COMB_DIR"
      "$AR" x "$BASE_LIBC"
    )

    echo "[lmbench] adding libtirpc objects from $TIRPC_MERGE_DIR..."
    cp "${tirpc_objs[@]}" "$COMB_DIR/"

    echo "[lmbench] creating combined libc.a -> $COMBINED_LIBC"
    (
      cd "$COMB_DIR"
      "$AR" rcs "$COMBINED_LIBC" ./*.o
      "$RANLIB" "$COMBINED_LIBC" || true
    )

    printf '%s\n' "$current_libc_sig" >"$LIBC_SIG_FILE"
  else
    echo "[lmbench] reusing combined libc.a"
  fi

  if ! cmp -s "$COMBINED_LIBC" "$BASE_LIBC"; then
    cp "$COMBINED_LIBC" "$BASE_LIBC"
  fi
fi

##################
# This is the second cache decision: even if the combined libc is current, the
# lmbench binaries themselves may or may not need a clean rebuild. We only ask
# for `make clean` when the build signature changed or the expected output tree
# is missing.
##################
current_build_sig="$(build_signature)"
need_clean=0
if [[ "$FORCE_CLEAN" == "1" || "$FORCE_CONFIGURE" == "1" ]]; then
  need_clean=1
fi
if [[ ! -f "$BUILD_SIG_FILE" ]] || [[ "$(cat "$BUILD_SIG_FILE" 2>/dev/null || true)" != "$current_build_sig" ]]; then
  need_clean=1
fi
if [[ ! -d "$LM_BENCH_BIN_DIR" ]]; then
  need_clean=1
fi

echo "[lmbench] building suite with REAL_CC='$REAL_CC'"
(
  cd "$REPO_ROOT/lmbench/src"

  if (( need_clean )); then
    echo "[lmbench] cleaning previous outputs..."
    make clean || true
  else
    echo "[lmbench] reusing previous build outputs..."
  fi

  make -j"$JOBS" \
    OS="wasm32-wasi" \
    O="../bin/wasm32-wasi" \
    CC="$REAL_CC" \
    CFLAGS="$CFLAGS" \
    CPPFLAGS="-I$MERGED_SYSROOT/include/tirpc" \
    LDFLAGS="$LDFLAGS" \
    LDLIBS="$LDLIBS" \
    all
)
printf '%s\n' "$current_build_sig" >"$BUILD_SIG_FILE"

OUT_DIR="$APPS_LMBENCH_CANON_ROOT/bin"
mkdir -p "$OUT_DIR"

echo "[lmbench] staging binaries from $LM_BENCH_BIN_DIR -> $OUT_DIR"

if [[ ! -d "$LM_BENCH_BIN_DIR" ]]; then
  echo "[lmbench] ERROR: expected lmbench output dir '$LM_BENCH_BIN_DIR' not found" >&2
  exit 1
fi

##################
# The original script removed the entire staging directory unconditionally.
# Here we only clear staged files inside it, which is enough to keep the
# outputs accurate without paying for more directory churn than necessary.
##################
find "$OUT_DIR" -maxdepth 1 -type f -delete
find "$LM_BENCH_BIN_DIR" -maxdepth 1 -type f \( -name '*.raw.wasm' -o -name '*.opt.wasm' -o -name '*.cwasm' -o -name '*.opt.wasm.cwasm' \) -delete

shopt -s nullglob
bin_files=("$LM_BENCH_BIN_DIR"/*)
shopt -u nullglob

have_files=0
for f in "${bin_files[@]}"; do
  case "$f" in
    *.o|*.a|*.cwasm|*.opt.wasm|*.opt.wasm.cwasm|*/lmbench) continue ;;
  esac
  have_files=1
done

if (( have_files == 0 )); then
  echo "[lmbench] ERROR: no non-.o binaries found in $LM_BENCH_BIN_DIR" >&2
  exit 1
fi

##################
# Lind expects the runtime module to include the epoch-injection transform, and
# issue #127 further requires the final staged executable name to be backed by
# the generated `.cwasm` artifact.
##################
if [[ ! -x "$WASM_OPT" ]]; then
  echo "[lmbench] ERROR: wasm-opt not found at '$WASM_OPT'; cannot produce runnable Lind artifacts."
  exit 1
fi

echo "[lmbench] post-processing staged binaries under $OUT_DIR ..."

shopt -s nullglob
stage_bins=("$LM_BENCH_BIN_DIR"/*)
shopt -u nullglob

for f in "${stage_bins[@]}"; do
  case "$f" in
    *.o|*.a|*.cwasm|*.opt.wasm|*.opt.wasm.cwasm|*.raw.wasm|*/lmbench) continue ;;
  esac
  if [[ ! -x "$f" ]]; then
    continue
  fi
  base="$(basename -- "$f")"
  RAW_OUT="$LM_BENCH_BIN_DIR/${base}.raw.wasm"
  OPT_OUT="$LM_BENCH_BIN_DIR/${base}.opt.wasm"
  run_limited "$JOBS" run_wasm_opt_replace "$f" "$RAW_OUT" "$OPT_OUT"
done

if ! wait_for_background_jobs; then
  echo "[lmbench] ERROR: wasm-opt post-processing failed." >&2
  exit 1
fi

##################
# For dynamic linking, each optimized binary needs extra exports added via
# add-export-tool. These exports (__wasm_apply_tls_relocs, __wasm_apply_global_relocs,
# __stack_pointer) are required by lind-boot to wire up the dynamically loaded
# modules at runtime.
##################
if [[ "$LIND_DYLINK" == "1" ]]; then
  echo "[lmbench] adding dylink exports via add-export-tool..."
  shopt -s nullglob
  dylink_opts=("$LM_BENCH_BIN_DIR"/*.opt.wasm)
  shopt -u nullglob
  for w in "${dylink_opts[@]}"; do
    "$ADD_EXPORT_TOOL" "$w" "$w" __wasm_apply_tls_relocs func __wasm_apply_tls_relocs optional
    "$ADD_EXPORT_TOOL" "$w" "$w" __wasm_apply_global_relocs func __wasm_apply_global_relocs optional
    "$ADD_EXPORT_TOOL" "$w" "$w" __stack_pointer global __stack_pointer
  done
fi

##################
# Issue #127 requires the final staged executable names to come from `.cwasm`
# outputs. We therefore require `lind-boot --precompile`, fail the build if it
# does not produce the expected artifacts, and then copy each `.cwasm` back to
# its extensionless executable name in the staging directory.
##################
if [[ ! -x "$LIND_BOOT" ]]; then
  echo "[lmbench] ERROR: lind-boot not found at '$LIND_BOOT'; cannot produce required cwasm artifacts." >&2
  exit 1
fi

echo "[lmbench] generating cwasm via lind-boot --precompile..."
shopt -s nullglob
opt_files=("$LM_BENCH_BIN_DIR"/*.opt.wasm)
shopt -u nullglob

if (( ${#opt_files[@]} == 0 )); then
  echo "[lmbench] ERROR: no optimized .opt.wasm files were produced under $LM_BENCH_BIN_DIR" >&2
  exit 1
fi

for w in "${opt_files[@]}"; do
  run_limited "$JOBS" "$LIND_BOOT" --precompile "$w"
done

if ! wait_for_background_jobs; then
  echo "[lmbench] ERROR: lind-boot --precompile failed." >&2
  exit 1
fi

for w in "${opt_files[@]}"; do
  FINAL_BIN="$OUT_DIR/$(basename -- "${w%.opt.wasm}")"
  OPT_CWASM="${w%.wasm}.cwasm"
  CLEAN_CWASM="${OPT_CWASM/.opt/}"
  if [[ "$OPT_CWASM" != "$CLEAN_CWASM" && -f "$OPT_CWASM" ]]; then
    mv "$OPT_CWASM" "$CLEAN_CWASM"
  fi
  if [[ ! -f "$CLEAN_CWASM" ]]; then
    echo "[lmbench] ERROR: expected cwasm artifact '$CLEAN_CWASM' was not produced." >&2
    exit 1
  fi
  cp "$CLEAN_CWASM" "$FINAL_BIN"
done

if [[ "$ARTIFACT_MODE" != "full" ]]; then
  find "$LM_BENCH_BIN_DIR" -maxdepth 1 -type f -name '*.opt.wasm' -delete
fi

echo "[lmbench] post-processing complete."

if [[ "$LIND_DYLINK" == "1" ]]; then
  echo ""
  echo "[lmbench] NOTE: dylink mode requires libtirpc.so at runtime."
  echo "[lmbench] Run with: lind-boot --preload env=/lib/libc.cwasm --preload env=/lib/libm.cwasm --preload env=/lib/libtirpc.so <binary>"
fi
