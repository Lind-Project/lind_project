#!/bin/bash

echo "alias gcc-4='/usr/local/gcc-4.4.3/bin/gcc'" >> "$HOME/.bashrc"
source "$HOME/.bashrc"

echo "Compiling native test binaries"
gcc-4 scripts/uds_send_recv.c -o scripts/uds -O3 -std=gnu99 -lrt -lpthread

echo "Compiling lind test binaries"
x86_64-nacl-gcc scripts/uds_send_recv.c -o scripts/uds.nexe -std=gnu99 -O3 -lrt -lpthread
lindfs cp /home/lind/lind_project/tests/ipc_performance/uds/scripts/uds.nexe /uds

echo "Compiling unsafe test binaries"
export LD_LIBRARY_PATH=/home/lind/lind_project/tests/native-rustposix:$LD_LIBRARY_PATH
/usr/local/gcc-4.4.3/bin/gcc -c /home/lind/lind_project/tests/native-rustposix/tests/lind_platform.c -o /home/lind/lind_project/tests/native-rustposix/tests/lind_platform.o -O3
/usr/local/gcc-4.4.3/bin/gcc -c scripts/uds_send_recv.c -o scripts/uds_send_recv.o -I/home/lind/lind_project/tests/native-rustposix/tests/ -std=gnu99 -O3 -lpthread
/usr/local/gcc-4.4.3/bin/gcc scripts/uds_send_recv.o /home/lind/lind_project/tests/native-rustposix/tests/lind_platform.o -L/home/lind/lind_project/src/safeposix-rust/target/release -lrustposix -o scripts/unsafe-uds -O3
