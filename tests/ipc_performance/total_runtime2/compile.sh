#!/bin/bash

# echo "Compiling native test binaries"
# gcc scripts/read.c -o readpipe -O3
# gcc scripts/write.c -o writepipe -O3

echo "Compiling raw test binaries"
x86_64-nacl-gcc scripts/read.c -o scripts/readpipe.nexe -std=gnu99 -lrt -O3
x86_64-nacl-gcc scripts/write.c -o scripts/writepipe.nexe -std=gnu99 -lrt -O3