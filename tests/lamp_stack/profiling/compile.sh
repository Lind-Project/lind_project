#!/bin/bash

echo "Compiling lind test binaries"
x86_64-nacl-gcc pwrite_test.c -o pwrite_test.nexe -std=gnu99 -lpthread
lindfs cp /home/lind/lind_project/tests/lamp_stack/profiling/pwrite_test.nexe /pwrite_test
