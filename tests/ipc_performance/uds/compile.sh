#!/bin/bash

echo "alias gcc-4='/usr/local/gcc-4.4.3/bin/gcc'" >> "$HOME/.bashrc"
source "$HOME/.bashrc"

echo "Compiling native test binaries"
gcc-4 scripts/uds_send_recv.c -o scripts/uds -O3 -std=gnu99 -lrt

echo "Compiling lind test binaries"
x86_64-nacl-gcc scripts/uds_send_recv.c -o scripts/uds.nexe -std=gnu99 -O3 -lrt
lindfs cp /home/lind/lind_project/tests/ipc_performance/uds/scripts/uds.nexe /uds
