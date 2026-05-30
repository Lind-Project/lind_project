#!/usr/bin/env bash
set -euo pipefail

# Portable libtirpc build for WASI; no apt, no sudo.
SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
: "${LIND_WASM_ROOT:=${LIND_WASM_ROOT:-$(cd "$REPO_ROOT/.." && pwd)/lind-wasm}}"

BASE_SYSROOT="${BASE_SYSROOT:-$LIND_WASM_ROOT/src/glibc/sysroot}"
LLVM_BIN="${LLVM_BIN:-$(ls -d "$LIND_WASM_ROOT"/clang+llvm-*/bin 2>/dev/null | head -n1)}"
WASM_OPT="${WASM_OPT:-$LIND_WASM_ROOT/tools/binaryen/bin/wasm-opt}"
if [[ -z "${LLVM_BIN}" || ! -x "$LLVM_BIN/clang" ]]; then
  echo "[libtirpc] ERROR: LLVM not found under $LIND_WASM_ROOT" >&2; exit 1
fi
if [[ ! -r "$BASE_SYSROOT/include/wasm32-wasi/stdio.h" ]]; then
  echo "[libtirpc] ERROR: sysroot headers missing at $BASE_SYSROOT" >&2; exit 1
fi

CC_WASI="$LLVM_BIN/clang --target=wasm32-unknown-wasi --sysroot=$BASE_SYSROOT"
AR="$LLVM_BIN/llvm-ar"
RANLIB="$LLVM_BIN/llvm-ranlib"

OVERLAY="$REPO_ROOT/build/sysroot_overlay"
MERGE_TMP="$OVERLAY/usr/lib/wasm32-wasi/merge_tmp"
LIND_DYLINK="${LIND_DYLINK:-0}"
mkdir -p "$OVERLAY/usr/include/tirpc" "$MERGE_TMP"

echo "[libtirpc] CC=$CC_WASI"
pushd "$REPO_ROOT/libtirpc" >/dev/null

autoreconf -fi

# ---------------------------------------------------------
# Branch libtirpc build flags based on Dylink mode
# ---------------------------------------------------------
if [[ "$LIND_DYLINK" == "1" ]]; then
  echo "[libtirpc] Building with PIC and default visibility for Dynamic Linking..."
  EXTRA_CFLAGS="-fPIC -fvisibility=default"
  CONFIG_ARGS="--disable-shared --enable-static --with-pic"
else
  echo "[libtirpc] Building standard static objects for Static Linking..."
  EXTRA_CFLAGS=""
  CONFIG_ARGS="--disable-shared --enable-static"
fi

CC="$CC_WASI" AR="$AR" RANLIB="$RANLIB" \
CFLAGS="--sysroot=$BASE_SYSROOT -O2 -g $EXTRA_CFLAGS" \
LDFLAGS="--sysroot=$BASE_SYSROOT" \
PKG_CONFIG=false \
./configure --host=wasm32-unknown-wasi \
  --disable-gssapi \
  $CONFIG_ARGS \
  --sysconfdir=/etc \
  ac_cv_func_malloc_0_nonnull=yes \
  ac_cv_func_memset=yes \
  ac_cv_func_strchr=yes


make -j
rsync -a "tirpc/" "$OVERLAY/usr/include/tirpc/"
find "src" -name '*.o' -exec cp {} "$MERGE_TMP/" \;
"$AR" rcs "$OVERLAY/usr/lib/wasm32-wasi/libtirpc.a" "$MERGE_TMP"/*.o
"$RANLIB" "$OVERLAY/usr/lib/wasm32-wasi/libtirpc.a"

popd >/dev/null
if [[ "$LIND_DYLINK" != "1" ]]; then
	echo "[libtirpc] done → $OVERLAY/usr/lib/wasm32-wasi/libtirpc.a"
	exit 0
fi

mkdir -p "$OVERLAY/lib"
ADD_EXPORT_TOOL="$LIND_WASM_ROOT/tools/add-export-tool/add-export-tool"

STATIC_LIB="$OVERLAY/usr/lib/wasm32-wasi/libtirpc.a"
DYNAMIC_LIB_WASM="$OVERLAY/usr/lib/wasm32-wasi/libtirpc.wasm"
DYNAMIC_LIB_OPT="$OVERLAY/usr/lib/wasm32-wasi/libtirpc.opt.wasm"
DYNAMIC_LIB_OPT_CWASM="$OVERLAY/usr/lib/wasm32-wasi/libtirpc.opt.cwasm"
DYNAMIC_STAGED_LIB="$OVERLAY/lib/libtirpc.so"
"$LLVM_BIN/clang" \
    --target=wasm32-unknown-wasi \
    -fPIC \
    --sysroot "$BASE_SYSROOT" \
    -fvisibility=default \
    -Wl,--import-memory \
    -Wl,--shared-memory \
    -Wl,--export-dynamic \
    -Wl,--experimental-pic \
    -Wl,--unresolved-symbols=import-dynamic \
    -Wl,-shared \
    -Wl,--whole-archive \
    "$STATIC_LIB" \
    -Wl,--no-whole-archive \
    "$LIND_WASM_ROOT/src/glibc/build/lind_debug.o" \
    -g -O0 -o "$DYNAMIC_LIB_WASM" || { echo "[libtirpc] ERROR: clang compilation failed" >&2; exit 1; }


if [[ ! -f "$DYNAMIC_LIB_WASM" ]]; then
  echo "[libtirpc] ERROR: Failed to generate '$DYNAMIC_LIB_WASM'; Exiting.." >&2
  exit 1
fi

"$ADD_EXPORT_TOOL" "$DYNAMIC_LIB_WASM" "$DYNAMIC_LIB_WASM" __wasm_apply_tls_relocs func __wasm_apply_tls_relocs optional || { echo "[libtirpc] ERROR: add-export-tool tls failed" >&2; exit 1; }

"$ADD_EXPORT_TOOL" "$DYNAMIC_LIB_WASM" "$DYNAMIC_LIB_WASM" __wasm_apply_global_relocs func __wasm_apply_global_relocs optional || { echo "[libtirpc] ERROR: add-export-tool global failed" >&2; exit 1; }

"$ADD_EXPORT_TOOL" "$DYNAMIC_LIB_WASM" "$DYNAMIC_LIB_WASM"  __stack_pointer global __stack_pointer optional || { echo "[libtirpc] ERROR: add-export-tool stack pointer failed" >&2; exit 1; }


$WASM_OPT --enable-bulk-memory --enable-threads --epoch-injection --pass-arg=epoch-import --asyncify --pass-arg=asyncify-import-globals -O2 --debuginfo "$DYNAMIC_LIB_WASM" -o "$DYNAMIC_LIB_OPT" || { echo "[libtirpc] ERROR: wasm-opt failed on '$DYNAMIC_LIB_OPT'; Exiting.." >&2; exit 1; }

if [[ ! -f "$DYNAMIC_LIB_OPT" ]]; then
  echo "[libtirpc] ERROR: Failed to generate '$DYNAMIC_LIB_OPT'; Exiting.." >&2
  exit 1
fi

# do precompile
$LIND_WASM_ROOT/scripts/lind_compile --precompile-only "$DYNAMIC_LIB_OPT" || { echo "[libtirpc] ERROR: lind_compile failed on '$DYNAMIC_LIB_OPT_CWASM'; Exiting.." >&2; exit 1; }

if [[ ! -f "$DYNAMIC_LIB_OPT_CWASM" ]]; then
  echo "[libtirpc] ERROR: Failed to generate '$DYNAMIC_LIB_OPT_CWASM'; Exiting.." >&2
  exit 1
fi

cp "$DYNAMIC_LIB_OPT_CWASM" "$DYNAMIC_STAGED_LIB"
echo "[libtirpc] Dynamic shared library staged as $DYNAMIC_STAGED_LIB"

