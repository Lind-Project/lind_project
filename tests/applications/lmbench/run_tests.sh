#!/usr/bin/env bash
set -u
set -o pipefail

#####################################
# lmbench smoke-test harness
#
# This script runs a curated lmbench smoke suite defined in
# `lmbench/test-binaries.txt`.
#
# Each non-comment line in that file is treated as one lmbench test command:
#   bin/<binary> [args...]
#
# The harness:
#   1. Verifies the active Lind runtime is using release mode.
#   2. Stages each referenced lmbench binary from `build/lmbench/bin` into
#      the Lind filesystem under `lindfs/bin`.
#   3. Creates the small lmbench-specific test assets needed by file-based
#      benchmarks under `lindfs/tmp/lmbench-test`.
#   4. Runs each command via `lind_run`.
#   5. Logs stdout/stderr, exit status, and a PASS/FAIL result for every test
#      to `lmbench/lmbench_test.log`.
#   6. Continues after failures and prints a summary at the end.
#
# This is intentionally a smoke suite, not a full benchmark campaign. The
# command list is kept in `test-binaries.txt` so it is easy to tune without
# editing the harness logic.
#####################################

PREFIX="[lmbench-test]"
RUN_COUNT=0
PASS_COUNT=0
FAIL_COUNT=0
FAILURES=()

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
APPS_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

resolve_lind_wasm_root() {
    if [[ -n "${LIND_WASM_ROOT:-}" && -d "${LIND_WASM_ROOT}" ]]; then
        printf '%s\n' "$LIND_WASM_ROOT"
        return 0
    fi

    if [[ -f "$APPS_ROOT/../scripts/lind_run" && -f "$APPS_ROOT/../Makefile" ]]; then
        (cd "$APPS_ROOT/.." && pwd)
        return 0
    fi

    if [[ -f "$APPS_ROOT/../lind-wasm/scripts/lind_run" && -f "$APPS_ROOT/../lind-wasm/Makefile" ]]; then
        (cd "$APPS_ROOT/../lind-wasm" && pwd)
        return 0
    fi

    return 1
}

LIND_WASM_ROOT="${LIND_WASM_ROOT:-$(resolve_lind_wasm_root 2>/dev/null || true)}"
LINDFS_ROOT="$LIND_WASM_ROOT/lindfs"
LIND_RUN="${LIND_RUN:-$LIND_WASM_ROOT/scripts/lind_run}"
BUILD_BIN_DIR="$APPS_ROOT/build/lmbench/bin"
TEST_LIST_FILE="${TEST_LIST_FILE:-$SCRIPT_DIR/test-binaries.txt}"
LOG_FILE="${LOG_FILE:-$SCRIPT_DIR/lmbench_test.log}"

TEST_TIMEOUT_SECONDS="${TEST_TIMEOUT_SECONDS:-60}"

TMP_DIR_GUEST="/tmp/lmbench-test"
TMP_DIR_HOST="$LINDFS_ROOT${TMP_DIR_GUEST}"
LARGE_FILE_GUEST="${TMP_DIR_GUEST}/sample_large.bin"
LARGE_FILE_HOST="${TMP_DIR_HOST}/sample_large.bin"
FS_DIR_GUEST="${TMP_DIR_GUEST}/fs_dir"
FS_DIR_HOST="${TMP_DIR_HOST}/fs_dir"

print_release_switch_instructions() {
    local runtime_root="$1"

    printf '%s\n' "To switch to release mode, run:" >&2
    printf '  cd %s\n' "$runtime_root" >&2
    printf '%s\n' "  make lind-boot" >&2
    printf '  cd %s\n' "$APPS_ROOT" >&2
    printf '%s\n' "  make lmbench" >&2
    printf '%s\n' "  ./lmbench/test.sh" >&2
    printf '%s\n' "This rebuilds lind-wasm/src/lind-boot/target/release/lind-boot, copies it to lind-wasm/build/lind-boot, then rebuilds lmbench from the apps Makefile before re-running this check." >&2
    printf '%s\n' "Release mode is set by rebuilding lind-wasm/build/lind-boot in release mode, and the apps-side rebuild step is make lmbench." >&2
}

# Temporary workaround for the current dev-vs-release issue: this is kept as a
# self-contained block inside lmbench/test.sh on purpose so it is easy to
# remove once the underlying issue is fixed.
verify_release_runtime_mode() {
    local runtime_root=""
    local active_lind_boot=""
    local debug_lind_boot=""
    local release_lind_boot=""

    runtime_root="$(resolve_lind_wasm_root || true)"

    if [[ -z "$runtime_root" ]]; then
        printf '%s\n' "ERROR: Could not locate the lind-wasm checkout, so release mode could not be verified." >&2
        print_release_switch_instructions "/path/to/lind-wasm"
        exit 1
    fi

    active_lind_boot="$runtime_root/build/lind-boot"
    debug_lind_boot="$runtime_root/src/lind-boot/target/debug/lind-boot"
    release_lind_boot="$runtime_root/src/lind-boot/target/release/lind-boot"

    if [[ ! -x "$active_lind_boot" ]]; then
        printf 'ERROR: Active lind-boot not found at %s\n' "$active_lind_boot" >&2
        print_release_switch_instructions "$runtime_root"
        exit 1
    fi

    if [[ -f "$debug_lind_boot" ]] && cmp -s "$active_lind_boot" "$debug_lind_boot"; then
        printf 'ERROR: Active lind-boot is running in dev/debug mode: %s\n' "$active_lind_boot" >&2
        print_release_switch_instructions "$runtime_root"
        exit 1
    fi

    if [[ -f "$release_lind_boot" ]] && cmp -s "$active_lind_boot" "$release_lind_boot"; then
        return 0
    fi

    if command -v strings >/dev/null 2>&1; then
        if strings "$active_lind_boot" 2>/dev/null | grep -q '/target/debug/'; then
            printf 'ERROR: Active lind-boot appears to be running in dev/debug mode: %s\n' "$active_lind_boot" >&2
            print_release_switch_instructions "$runtime_root"
            exit 1
        fi

        if strings "$active_lind_boot" 2>/dev/null | grep -q '/target/release/'; then
            return 0
        fi
    fi

    printf '%s\n' "ERROR: Could not verify that lind-boot is running in release mode." >&2
    printf 'Expected active runtime: %s\n' "$active_lind_boot" >&2
    print_release_switch_instructions "$runtime_root"
    exit 1
}

append_log() {
    printf '%s\n' "$*" >>"$LOG_FILE"
}

append_log_file() {
    local file_path="$1"

    if [[ -s "$file_path" ]]; then
        cat "$file_path" >>"$LOG_FILE"
    else
        append_log "(no output)"
    fi
}

command_to_string() {
    local rendered=""
    local part

    for part in "$@"; do
        rendered+="$(printf '%q' "$part") "
    done

    printf '%s' "${rendered% }"
}

parse_test_line() {
    local test_line="$1"
    local array_name="$2"
    local -n parsed_args_ref="$array_name"

    parsed_args_ref=()
    read -r -a parsed_args_ref <<<"$test_line"
}

prepare_test_assets() {
    rm -rf "$TMP_DIR_HOST"
    mkdir -p "$TMP_DIR_HOST" "$FS_DIR_HOST"
    dd if=/dev/zero of="$LARGE_FILE_HOST" bs=1M count=8 status=none
}

run_with_timeout() {
    local output_file="$1"
    shift

    local runner_pid=0
    local rc=0
    local use_process_group=0
    local deadline=0

    if command -v setsid >/dev/null 2>&1; then
        setsid "$@" >"$output_file" 2>&1 &
        use_process_group=1
    else
        "$@" >"$output_file" 2>&1 &
    fi
    runner_pid=$!
    deadline=$((SECONDS + TEST_TIMEOUT_SECONDS))

    while kill -0 "$runner_pid" 2>/dev/null; do
        if (( SECONDS >= deadline )); then
            append_log "# Timeout: exceeded ${TEST_TIMEOUT_SECONDS}s"
            if (( use_process_group )); then
                kill -TERM -- "-$runner_pid" 2>/dev/null || true
            else
                kill -TERM "$runner_pid" 2>/dev/null || true
            fi
            sleep 2
            if (( use_process_group )); then
                kill -KILL -- "-$runner_pid" 2>/dev/null || true
            else
                kill -KILL "$runner_pid" 2>/dev/null || true
            fi
            wait "$runner_pid" 2>/dev/null || true
            return 124
        fi
        sleep 1
    done

    wait "$runner_pid"
    rc=$?
    return "$rc"
}

stage_required_binaries() {
    local test_line=""
    local -a parsed_args=()
    local binary_guest_path=""
    local binary_name=""
    local source_path=""
    local destination_path=""

    while IFS= read -r test_line; do
        [[ -z "$test_line" ]] && continue
        [[ "$test_line" =~ ^[[:space:]]*# ]] && continue

        parse_test_line "$test_line" parsed_args
        (( ${#parsed_args[@]} > 0 )) || continue

        binary_guest_path="${parsed_args[0]}"
        binary_name="${binary_guest_path##*/}"
        source_path="$BUILD_BIN_DIR/$binary_name"
        destination_path="$LINDFS_ROOT/$binary_guest_path"

        if [[ ! -f "$source_path" ]]; then
            printf '%s ERROR: missing build binary %s\n' "$PREFIX" "$source_path" >&2
            return 1
        fi

        mkdir -p "$(dirname "$destination_path")"
        cp "$source_path" "$destination_path"
    done <"$TEST_LIST_FILE"
}

begin_test_section() {
    local binary_name="$1"
    local test_line="$2"

    RUN_COUNT=$((RUN_COUNT + 1))

    printf '[START] %s\n' "$binary_name"

    append_log ""
    append_log "#####################################"
    append_log "# Binary: $binary_name"
    append_log "# Command: $test_line"
    append_log "# Started: $(date -u +"%Y-%m-%dT%H:%M:%SZ")"
    append_log "#####################################"
}

finish_test_section() {
    local binary_name="$1"
    local test_rc="$2"

    if [[ "$test_rc" -eq 0 ]]; then
        PASS_COUNT=$((PASS_COUNT + 1))
        append_log "# Result: PASS"
        printf '[PASS] %s\n' "$binary_name"
    else
        FAIL_COUNT=$((FAIL_COUNT + 1))
        FAILURES+=("$binary_name")
        append_log "# Result: FAIL (exit $test_rc)"
        printf '[FAIL] %s (exit %s)\n' "$binary_name" "$test_rc"
    fi

    append_log "#####################################"
}

run_configured_test() {
    local test_line="$1"
    local -a parsed_args=()
    local binary_guest_path=""
    local binary_name=""
    local output_file=""
    local rc=0

    parse_test_line "$test_line" parsed_args
    (( ${#parsed_args[@]} > 0 )) || return 0

    binary_guest_path="${parsed_args[0]}"
    binary_name="${binary_guest_path##*/}"

    begin_test_section "$binary_name" "$test_line"

    if [[ ! -f "$LINDFS_ROOT/$binary_guest_path" ]]; then
        append_log "# Error: missing staged binary at $LINDFS_ROOT/$binary_guest_path"
        finish_test_section "$binary_name" 1
        return 1
    fi

    output_file="$(mktemp)"
    append_log "# lind_run Command: $(command_to_string "$LIND_RUN" "${parsed_args[@]}")"

    run_with_timeout "$output_file" "$LIND_RUN" "${parsed_args[@]}"
    rc=$?

    append_log "# Output:"
    append_log_file "$output_file"
    append_log "# Exit Code: $rc"

    rm -f "$output_file"

    finish_test_section "$binary_name" "$rc"
    return "$rc"
}

write_summary() {
    local failed_list=""

    if (( ${#FAILURES[@]} == 0 )); then
        failed_list="(none)"
    else
        failed_list="${FAILURES[*]}"
    fi

    append_log ""
    append_log "#####################################"
    append_log "# Summary"
    append_log "# Ran: $RUN_COUNT"
    append_log "# Passed: $PASS_COUNT"
    append_log "# Failed: $FAIL_COUNT"
    append_log "# Failed Binaries: $failed_list"
    append_log "#####################################"

    printf '%s %d/%d tests passed, %d failed\n' \
        "$PREFIX" "$PASS_COUNT" "$RUN_COUNT" "$FAIL_COUNT"
    printf '%s Log saved to: %s\n' "$PREFIX" "$LOG_FILE"

    if (( FAIL_COUNT > 0 )); then
        printf '%s failed binaries: %s\n' "$PREFIX" "$failed_list"
    fi
}

main() {
    local test_line=""

    if [[ -z "$LIND_WASM_ROOT" ]]; then
        printf '%s ERROR: could not determine LIND_WASM_ROOT\n' "$PREFIX" >&2
        exit 1
    fi

    : >"$LOG_FILE"

    append_log "#####################################"
    append_log "# lmbench smoke test log"
    append_log "# Started: $(date -u +"%Y-%m-%dT%H:%M:%SZ")"
    append_log "# APPS_ROOT: $APPS_ROOT"
    append_log "# LIND_WASM_ROOT: $LIND_WASM_ROOT"
    append_log "# LINDFS_ROOT: $LINDFS_ROOT"
    append_log "# BUILD_BIN_DIR: $BUILD_BIN_DIR"
    append_log "# TEST_LIST_FILE: $TEST_LIST_FILE"
    append_log "# lind_run: $LIND_RUN"
    append_log "# Timeout Seconds: $TEST_TIMEOUT_SECONDS"
    append_log "#####################################"

    if [[ ! -x "$LIND_RUN" ]]; then
        printf '%s ERROR: lind_run not found at %s\n' "$PREFIX" "$LIND_RUN" >&2
        exit 1
    fi

    if [[ ! -d "$BUILD_BIN_DIR" ]]; then
        printf '%s ERROR: lmbench build bin directory not found at %s\n' "$PREFIX" "$BUILD_BIN_DIR" >&2
        exit 1
    fi

    if [[ ! -d "$LINDFS_ROOT" ]]; then
        printf '%s ERROR: lindfs root not found at %s\n' "$PREFIX" "$LINDFS_ROOT" >&2
        exit 1
    fi

    if [[ ! -f "$TEST_LIST_FILE" ]]; then
        printf '%s ERROR: test list not found at %s\n' "$PREFIX" "$TEST_LIST_FILE" >&2
        exit 1
    fi

    verify_release_runtime_mode
    prepare_test_assets
    stage_required_binaries

    cd "$LINDFS_ROOT" || exit 1

    while IFS= read -r test_line; do
        [[ -z "$test_line" ]] && continue
        [[ "$test_line" =~ ^[[:space:]]*# ]] && continue
        run_configured_test "$test_line" || true
    done <"$TEST_LIST_FILE"

    write_summary

    if (( FAIL_COUNT > 0 )); then
        exit 1
    fi

    exit 0
}

main "$@"
