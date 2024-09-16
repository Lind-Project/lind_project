#!/bin/bash

echo "Compiling native test binaries"
./scripts/compile-native.sh

echo "Compiling lind / rawposix test binaries"
./scripts/compile-lind.sh

echo "Compiling unsafe test binaries"
./scripts/compile-unsafe.sh
