#!/bin/bash

echo "Compiling native test binaries"
gcc scripts/buffer_read_write.c -o scripts/buffer_read_write -lpthread -std=gnu99 -O3

echo "Compiling lind test binaries"
x86_64-nacl-gcc scripts/buffer_read_write.c -o scripts/buffer_read_write.nexe -lpthread -std=gnu99 -O3
lindfs cp /home/lind/lind_project/tests/ipc_performance/buffer_read_write/scripts/buffer_read_write.nexe /buffer_read_write
