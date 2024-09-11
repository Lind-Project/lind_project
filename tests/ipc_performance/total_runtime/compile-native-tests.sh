#!/bin/bash

echo "Compiling native test binaries"
scripts/compile-native.sh

echo "Compiling 32 bit binaries"
scripts/compile-32.sh

echo "Compiling no libc test binaries"
scripts/compile-nolibc.sh
