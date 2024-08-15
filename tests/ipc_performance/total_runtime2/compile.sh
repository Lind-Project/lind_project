#!/bin/bash
echo "Compiling lind test binaries"
x86_64-nacl-gcc scripts/readnamed.c -o /home/lind/lind_project/src/safeposix-rust/tmp/readnamed.nexe -lrt -std=gnu99 -O3
x86_64-nacl-gcc scripts/writenamed.c -o /home/lind/lind_project/src/safeposix-rust/tmp/writenamed.nexe -lrt -std=gnu99 -O3