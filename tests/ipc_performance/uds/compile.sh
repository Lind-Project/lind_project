#!/bin/bash

echo "Compiling native test binaries"
gcc scripts/uds_send_recv.c -o scripts/uds -O3 -std=gnu99

echo "Compiling lind test binaries"
x86_64-nacl-gcc scripts/uds_send_recv.c -o scripts/uds.nexe -std=gnu99 -O3
# lindfs cp /home/lind/lind_project/tests/ipc_performance/uds/scripts/uds.nexe /uds
cp /home/lind/lind_project/tests/ipc_performance/uds/scripts/uds.nexe /home/lind/lind_project/src/safeposix-rust/tmp/uds
