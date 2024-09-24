#!/bin/bash

mkdir -p data/
./compile.sh

echo "---------------- Pipe ----------------"
echo "Running on lind stack"
python3 gen_bufdata.py -c $1 -p "lind /pipe"

echo -e "\nRunning on native linux"
python3 gen_bufdata.py -c $1 -p "scripts/pipe"

echo "---------------- UDS ----------------"
echo "Running on lind stack"
python3 gen_bufdata.py -c $1 -p "lind /uds"

echo -e "\nRunning on native linux"
python3 gen_bufdata.py -c $1 -p "scripts/uds"
