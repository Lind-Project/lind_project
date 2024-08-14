#!/bin/bash
echo "Compiling lind test binaries"
x86_64-nacl-gcc scripts/read.c -o scripts/readshort.nexe -std=gnu99 -lpthread -O3
x86_64-nacl-gcc scripts/write.c -o scripts/writeshort.nexe -std=gnu99 -lpthread -O3
x86_64-nacl-gcc scripts/short1proc.c -o scripts/short1proc.nexe -std=gnu99 -lpthread -O3