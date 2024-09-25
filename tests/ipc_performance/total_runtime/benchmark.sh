#!/bin/bash

# Compile binaries
./compile.sh

mkdir data/ 

# Run native / unsafe / lind tests
./run_pipe_performance.sh $1 other

# Setup rust compiler in sudo mode
rustup default nightly

# Install RawPOSIX
/home/lind/lind_project/src/scripts/rawposix/rawposix_install.sh

# Loading lind binaries into RawPOSIX file system
/home/lind/lind_project/src/scripts/rawposix/rawposix_base.sh

./run_pipe_performance.sh $1 rawposix