#!/bin/bash

mkdir -p data/
./compile.sh

echo "Running on lind stack"
# python3 gen_linduds.py -c $1 -t $2
python3 gen_udsdata.py -c $1 -t $2 -p "lind /uds"

echo -e "\nRunning on native linux"
# python3 gen_natuds.py -c $1 -t $2
python3 gen_udsdata.py -c $1 -t $2 -p "scripts/uds"

echo -e "\nCleaning up"
./cleanup.sh
