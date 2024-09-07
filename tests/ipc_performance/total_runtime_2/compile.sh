#!/bin/bash

echo "alias gcc-4='/usr/local/gcc-4.4.3/bin/gcc'" >> "$HOME/.bashrc"
source "$HOME/.bashrc"

echo "Compiling native test binaries"
scripts/compile-nat.sh

echo "Compiling lind test binaries"
scripts/compile-lind.sh