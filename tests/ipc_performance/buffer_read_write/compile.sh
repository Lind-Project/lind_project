#!/bin/bash

echo "Compiling native test binaries"
gcc scripts/buffer_read_write.c -o scripts/buffer_read_write -lpthread -std=gnu99 -O3 -lrt
gcc scripts/buffer_read_write_times.c -o scripts/buffer_read_write_times -lpthread -std=gnu99 -O3 -lrt
gcc scripts/buffer_read_write_call_times.c -o scripts/buffer_read_write_call_times -lpthread -std=gnu99 -O3 -lrt

echo "Compiling lind test binaries"
x86_64-nacl-gcc scripts/buffer_read_write.c -o scripts/buffer_read_write.nexe -lpthread -std=gnu99 -O3 -lrt
lindfs cp /home/lind/lind_project/tests/ipc_performance/buffer_read_write/scripts/buffer_read_write.nexe /buffer_read_write
x86_64-nacl-gcc scripts/buffer_read_write_times.c -o scripts/buffer_read_write_times.nexe -lpthread -std=gnu99 -O3 -lrt
lindfs cp /home/lind/lind_project/tests/ipc_performance/buffer_read_write/scripts/buffer_read_write_times.nexe /buffer_read_write_times
x86_64-nacl-gcc scripts/buffer_read_write_call_times.c -o scripts/buffer_read_write_call_times.nexe -lpthread -std=gnu99 -O3 -lrt
lindfs cp /home/lind/lind_project/tests/ipc_performance/buffer_read_write/scripts/buffer_read_write_call_times.nexe /buffer_read_write_call_times
