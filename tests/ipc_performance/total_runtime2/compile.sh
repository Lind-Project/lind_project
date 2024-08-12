#!/bin/bash

echo "Compiling native test binaries"
gcc scripts/read.c -o readpipe -O3
gcc scripts/write.c -o writepipe -O3

echo "Compiling lind test binaries"
x86_64-nacl-gcc scripts/read.c -o scripts/readpipe.nexe -std=gnu99 -O3
x86_64-nacl-gcc scripts/write.c -o scripts/writepipe.nexe -std=gnu99 -O3