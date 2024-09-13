#!/bin/bash

mkdir -p data/
./compile.sh

# echo "Running on lind stack"
# python3 gen_pipedata.py -c $1 -p "lind /pipe"

# echo -e "\nRunning on native linux"
# python3 gen_pipedata.py -c $1 -p "scripts/pipe"

echo "Running on lind stack"
python3 gen_pipechunk.py -c $1 -p "lind /pipe"

echo -e "\nRunning on native linux"
python3 gen_pipechunk.py -c $1 -p "scripts/pipe"

echo -e "\nCleaning up"
./cleanup.sh
