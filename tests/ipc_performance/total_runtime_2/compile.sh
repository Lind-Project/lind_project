#!/bin/bash

echo "Compiling native test binaries"
scripts/compile-nat.sh

echo "Compiling lind test binaries"
scripts/compile-lind.sh