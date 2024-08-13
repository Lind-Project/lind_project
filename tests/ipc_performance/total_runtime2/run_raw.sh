#!/bin/bash

echo "Copying scripts to rawfs"
cp /home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/pipescript.sh /home/lind/lind_project/src/safeposix-rust/pipescript.sh
cp /home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/writepipe.nexe /home/lind/lind_project/src/safeposix-rust/writepipe
cp /home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/readpipe.nexe /home/lind/lind_project/src/safeposix-rust/readpipe

echo "Varying write and read buffers"
python3 gen_rawps2.py -w x -r x -c $1

echo -e "\nVarying write buffers"
python3 gen_rawps2.py -w x -r 16 -c $1

echo -e "\nVarying read buffers"
python3 gen_rawps2.py -w 16 -r x -c $1