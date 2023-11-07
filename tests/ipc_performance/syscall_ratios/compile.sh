#!/bin/bash

echo "Compiling native test binaries"
gcc scripts/write_var_time.c -o scripts/write_var_time -lpthread -O3
gcc scripts/read_var_time.c -o scripts/read_var_time -lpthread -O3

echo "Compiling lind test binaries"
x86_64-nacl-gcc scripts/write_var_time.c -o scripts/write_var_time.nexe -std=gnu99 -lpthread -lrt -O3
x86_64-nacl-gcc scripts/read_var_time.c -o scripts/read_var_time.nexe -std=gnu99 -lpthread -lrt -O3
