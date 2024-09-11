#!/bin/bash

# Compile gcc-4 for native / bash and coreutils for lind
./setup.sh

# Compile binaries
./compile.sh

# Run native tests
./run_pipe_performance.sh $1 other