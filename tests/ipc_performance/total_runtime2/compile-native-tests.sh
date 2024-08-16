#!/bin/bash

echo "Compiling native test binaries"
/home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/compile-native.sh

echo "Compiling 32 bit binaries"
/home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/compile-32.sh

echo "Compiling no libc test binaries"
/home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/compile-nolibc.sh
