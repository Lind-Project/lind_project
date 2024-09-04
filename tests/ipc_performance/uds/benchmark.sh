#!/bin/bash

mkdir -p data/
./compile.sh

echo "Running on lind stack"
python3 gen_udsdata.py -c $1 -p "lind /uds"

echo -e "\nRunning on native linux"
python3 gen_udsdata.py -c $1 -p "scripts/uds"

echo -e "\nRunning on unsafe"
python3 gen_udsdata.py -c $1 -p "scripts/unsafe-uds"

echo -e "\nCleaning up"
./cleanup.sh
