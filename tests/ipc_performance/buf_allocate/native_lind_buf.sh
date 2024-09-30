#!/bin/bash

mkdir -p data/

echo "---------------- Pipe ----------------"
echo "Running on lind stack"
python3 gen_bufdata.py -c $1 -p "lind /pipe"

echo "---------------- UDS ----------------"
echo "Running on lind stack"
python3 gen_bufdata.py -c $1 -p "lind /uds"

