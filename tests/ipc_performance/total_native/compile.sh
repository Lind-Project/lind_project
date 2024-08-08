#!/bin/bash

echo "Compiling native test binaries"
gcc scripts/write32var.c -o scripts/write32var -lpthread -O3
gcc scripts/read32var.c -o scripts/read32var -lpthread -O3

gcc scripts/writenolibc32var.c -o scripts/writenolibc32var -lpthread -O3
gcc scripts/readnolibc32var.c -o scripts/readnolibc32var -lpthread -O3

gcc scripts/write32var.c -o scripts/write32-32var -lpthread -O3 -m32
gcc scripts/read32var.c -o scripts/read32-32var -lpthread -O3 -m32


