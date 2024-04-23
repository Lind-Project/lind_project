#!/bin/bash

echo "Varying write and read buffers"
python3 gen_natps2.py -w x -r x -c $1

echo -e "\nVarying write buffers"
python3 gen_natps2.py -w x -r 16 -c $1

echo -e "\nVarying read buffers"
python3 gen_natps2.py -w 16 -r x -c $1
