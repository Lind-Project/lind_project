#!/bin/bash

# Compile binaries
./compile.sh

mkdir data/ 

echo "SFI test"
python3 gen_sfidata.py $1
