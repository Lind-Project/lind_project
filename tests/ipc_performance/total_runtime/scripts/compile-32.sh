#!/bin/bash

echo "Compiling nolibc binaries"
/usr/local/gcc-4.4.3/bin/gcc scripts/read.c -o scripts/readpipe32 -std=gnu99 -O3 
/usr/local/gcc-4.4.3/bin/gcc scripts/write.c -o scripts/writepipe32 -std=gnu99 -O3
