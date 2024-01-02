#!/bin/bash

mkdir -p data/
./compile.sh

echo -e "Running on native linux"
python3 run_native_rw_call.py -c $1 -t $2

echo -e "\nRunning on lind stack"
python3 run_lind_rw_call.py -c $1 -t $2

echo -e "\nCleaning up"
./cleanup.sh
