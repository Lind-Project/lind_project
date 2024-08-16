#!/bin/bash

echo "Compiling nolibc binaries"
/usr/local/gcc-4.4.3/bin/gcc scripts/read-nolibc.c -o scripts/readpipe-nolibc -std=gnu99 -O3
/usr/local/gcc-4.4.3/bin/gcc scripts/write-nolibc.c -o scripts/writepipe-nolibc -std=gnu99 -O3
