#!/bin/bash

echo "Compile"
x86_64-nacl-gcc two-process-write-namedpp.c -o /home/lind/lind_project/src/safeposix-rust/tmp/two-process-write-namedpp.nexe
x86_64-nacl-gcc two-process-read-namedpp.c -o /home/lind/lind_project/src/safeposix-rust/tmp/two-process-read-namedpp.nexe

echo "Copying scripts to lindfs"
cp /home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/raw2proc.sh /home/lind/lind_project/src/safeposix-rust/tmp/raw2proc.sh
cp /home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/two-process-read-namedpp.nexe /home/lind/lind_project/src/safeposix-rust/tmp/two-process-read-namedpp.nexe
cp /home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/two-process-write-namedpp.nexe /home/lind/lind_project/src/safeposix-rust/tmp/two-process-write-namedpp.nexe


echo "Varying write and read buffers"
python3 gen_rawnamedpp2.py -w x -r x -c $1

echo -e "\nVarying write buffers"
python3 gen_rawnamedpp2.py -w x -r 16 -c $1

echo -e "\nVarying read buffers"
python3 gen_rawnamedpp2.py -w 16 -r x -c $1
