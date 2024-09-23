#!/bin/bash

echo "=============== Running SFI Tests ==============="

echo "=============== Running Unix Domain Socket v.s. Pipe Tests ==============="

# Setup rust compiler in sudo mode
rustup default nightly

# Run the IPC total runtime tests
echo "=============== Running IPC Total Runtime Tests ==============="
/home/lind/lind_project/tests/ipc_performance/total_runtime/benchmark.sh 1

