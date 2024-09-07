#!/bin/bash
echo "alias gcc-4='/usr/local/gcc-4.4.3/bin/gcc'" >> "$HOME/.bashrc"
source "$HOME/.bashrc"

gcc-4 scripts/pipe_write_read.c -o scripts/pipe -O3 -std=gnu99 -lrt -lpthread