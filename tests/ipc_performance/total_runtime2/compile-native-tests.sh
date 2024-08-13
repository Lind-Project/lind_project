#!/bin/bash

echo "Compiling nolibc binaries"
gcc scripts/read-nolibc.c -o scripts/readpipe-nolibc -O3
gcc scripts/write-nolibc.c -o scripts/writepipe-nolibc -O3

echo "Compiling nolibc binaries"
gcc scripts/read.c -o scripts/readpipei32 -O3
gcc scripts/write.c -o scripts/writepipe32 -O3

