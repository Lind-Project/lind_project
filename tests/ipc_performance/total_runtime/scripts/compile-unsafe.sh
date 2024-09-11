#!/bin/bash

export LIBRARY_PATH=/usr/lib/x86_64-linux-gnu

export LD_LIBRARY_PATH=/home/lind/lind_project/tests/native-rustposix:$LD_LIBRARY_PATH
/usr/local/gcc-4.4.3/bin/gcc -c /home/lind/lind_project/tests/native-rustposix/tests/lind_platform.c -o /home/lind/lind_project/tests/native-rustposix/tests/lind_platform.o -O3
/usr/local/gcc-4.4.3/bin/gcc -c scripts/unsafe-pipe.c -o scripts/unsafe-pipe.o -I/home/lind/lind_project/tests/native-rustposix/tests/ -std=gnu99 -O3
/usr/local/gcc-4.4.3/bin/gcc scripts/unsafe-pipe.o /home/lind/lind_project/tests/native-rustposix/tests/lind_platform.o -L/home/lind/lind_project/src/safeposix-rust/target/release -lrustposix -o scripts/unsafe-pipe -O3 -lpthread
