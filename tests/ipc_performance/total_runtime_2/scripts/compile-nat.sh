#!/bin/bash
gcc-4 scripts/pipe_write_read.c -o scripts/pipe -O3 -std=gnu99 -lrt -lpthread