#!/bin/bash

echo "Compiling native test binaries"
gcc scripts/write_var_time.c -o scripts/write_var_time -lpthread
gcc scripts/read_var_time.c -o scripts/read_var_time -lpthread

echo "Compiling lind test binaries"
x86_64-nacl-gcc scripts/write_var_time.c -o scripts/write_var_time.nexe -std=gnu99 -lpthread -lrt
x86_64-nacl-gcc scripts/read_var_time.c -o scripts/read_var_time.nexe -std=gnu99 -lpthread -lrt
