#!/bin/bash
echo "Compiling lind test binaries"
x86_64-nacl-gcc scripts/readnamed.c -o /home/lind/lind_project/src/safeposix-rust/tmp/readnamed.nexe -std=gnu99 -lpthread -O3
x86_64-nacl-gcc scripts/writenamed.c -o /home/lind/lind_project/src/safeposix-rust/tmp/writenamed.nexe -std=gnu99 -lpthread -O3