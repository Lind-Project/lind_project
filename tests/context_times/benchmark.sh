#!/bin/bash

mkdir -p data/
./compile.sh

python3 test_native.py -f tests.txt -c 10
python3 test_lind.py -f tests.txt -c 10
./cleanup.sh
