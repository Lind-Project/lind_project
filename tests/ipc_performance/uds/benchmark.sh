#!/bin/bash

mkdir -p data/
./compile.sh

echo "Running on lind stack"
python3 gen_linduds.py -c $1

echo -e "\nRunning on native linux"
python3 gen_natuds.py -c $1

echo -e "\nCleaning up"
./cleanup.sh
