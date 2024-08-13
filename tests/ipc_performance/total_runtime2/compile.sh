#!/bin/bash

echo "Compiling native test binaries"
gcc-4 scripts/read.c -o scripts/readpipe -O3
gcc-4 scripts/write.c -o scripts/writepipe -O3

echo "Compiling lind / rawposix test binaries"
x86_64-nacl-gcc scripts/read.c -o scripts/readpipe.nexe -std=gnu99 -lrt -O3
x86_64-nacl-gcc scripts/write.c -o scripts/writepipe.nexe -std=gnu99 -lrt -O3

echo "Compiling unsafe test binaries"
export LD_LIBRARY_PATH=/home/lind/lind_project/tests/native-rustposix:$LD_LIBRARY_PATH
gcc-4 -c /home/lind/lind_project/tests/native-rustposix/tests/lind_platform.c -o /home/lind/lind_project/tests/native-rustposix/tests/lind_platform.o -O3
gcc-4 -c scripts/unsafe-pipe.c -o scripts/unsafe-pipe.o -I/home/lind/lind_project/tests/native-rustposix/tests/ -std=gnu99 -O3
gcc-4 scripts/unsafe-pipe.o /home/lind/lind_project/tests/native-rustposix/tests/lind_platform.o -L/home/lind/lind_project/src/safeposix-rust/target/release -lrustposix -o scripts/unsafe-pipe -O3

