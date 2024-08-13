#!/bin/bash

echo "Compiling native test binaries"
/home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/compile-native.sh

echo "Compiling lind / rawposix test binaries"
/home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/compile-lind.sh

echo "Compiling unsafe test binaries"
/home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/compile-unsafe.sh
