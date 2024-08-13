#!/bin/bash

rm scripts/read*var scripts/write*var
rm scripts/read*var.nexe scripts/write*var.nexe

cd /home/lind/lind_project/tests/native-rustposix
make clean
cd /home/lind/lind_project/tests/ipc_performance/total_runtime
