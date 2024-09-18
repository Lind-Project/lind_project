#!/bin/bash

# Compile gcc-4 for native / bash and coreutils for lind
./setup.sh

# Compile binaries
./compile.sh

mkdir data/ 

# Run native tests
./run_pipe_performance.sh $1 other

# Install RawPOSIX
./rawposix_install.sh

./rawposix_base.sh

./run_pipe_performance.sh $1 raw