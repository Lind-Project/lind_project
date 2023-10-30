#!/bin/bash

echo "Compiling native test binaries"
gcc scripts/uds_test.c -o scripts/uds

echo "Compiling lind test binaries"
x86_64-nacl-gcc scripts/uds_test.c -o scripts/uds.nexe -std=gnu99
lindfs cp /home/lind/lind_project/tests/ipc_performance/uds/scripts/uds.nexe /uds
