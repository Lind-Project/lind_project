#!/bin/bash

# This tests will use regular RustPOSIX and Native linux only, so we run this test
# first with pre-built binaries
echo "=============== Running Unix Domain Socket v.s. Pipe Tests ==============="
/home/lind/lind_project/tests/ipc_performance/buf_allocate/benchmark.sh $1

# Setup rust compiler in sudo mode
rustup default nightly

# We need to compile RawPOSIX for IPC total runtime tests, so IPC tests will be 
# second run. Native / Unsafe / Lind + RustPOSIX wil run first and then benchmark.sh
# inside total_runtime folder will automatically recompile and reinstall RawPOSIX
echo "=============== Running IPC Total Runtime Tests ==============="
/home/lind/lind_project/tests/ipc_performance/total_runtime/benchmark.sh $1

# We will need to run write() with RustPOSIX under branch `libc-write`, but close()
# and getpid() with regular compiled RustPOSIX. So at first we'll re-compile the 
# RustPOSIX under normal then compile again to see the 
echo "=============== Running SFI Tests ==============="
/home/lind/lind_project/tests/ipc_performance/sfi_overhead/benchmark.sh $1