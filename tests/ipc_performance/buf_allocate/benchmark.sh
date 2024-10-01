#!/bin/bash

mkdir -p data/
./compile.sh

echo -e "\n---------------- Pipe ----------------\n"
echo "Running on lind stack"
python3 gen_bufdata.py -c $1 -p "lind /pipe"

echo -e "\nRunning on native linux"
python3 gen_bufdata.py -c $1 -p "scripts/pipe"

echo -e "\n---------------- UDS ----------------\n"
echo "Running on lind stack"
python3 gen_bufdata.py -c $1 -p "lind /uds"

echo -e "\nRunning on native linux"
python3 gen_bufdata.py -c $1 -p "scripts/uds"

echo -e "\n---------------- Loop Back ----------------\n"
echo "Running on lind stack"
python3 gen_bufdata.py -c $1 -p "lind /loopback"

echo -e "\nRunning on native linux"
python3 gen_bufdata.py -c $1 -p "scripts/loopback"
