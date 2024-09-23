#!/bin/bash

# Compile binaries
./compile.sh

mkdir data/ 
mkdir outputs/

echo "SFI test"
python3 gen_sfidata.py -c $1
