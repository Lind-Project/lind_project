#!/bin/bash

mkdir -p data/
./compile.sh

echo -e "Running on native linux"
python3 run_native.py -c $1

echo -e "\nRunning on lind stack"
python3 run_lind.py -c $1

echo -e "\nCleaning up"
./cleanup.sh
