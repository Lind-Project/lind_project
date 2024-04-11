#!/bin/bash

mkdir -p data/
./compile.sh

python3 test_native_pipe.py -c 5 -t 16
python3 test_lind_pipe.py -c 5 -t 16
./cleanup.sh
