#!/bin/bash

echo "Compile"
x86_64-nacl-gcc /home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/two-process-write-namedpp.c -o /home/lind/lind_project/src/safeposix-rust/tmp/two-process-write-namedpp.nexe -lpthread -O3
x86_64-nacl-gcc /home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/two-process-read-namedpp.c -o /home/lind/lind_project/src/safeposix-rust/tmp/two-process-read-namedpp.nexe -lpthread -O3
x86_64-nacl-gcc /home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/one-proces-namedpp.c -o /home/lind/lind_project/src/safeposix-rust/tmp/one-proces-namedpp.nexe -lpthread -O3

echo "Copying scripts to lindfs"
cp /home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/raw2proc.sh /home/lind/lind_project/src/safeposix-rust/tmp/raw2proc.sh
cp /home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/raw1proc.sh /home/lind/lind_project/src/safeposix-rust/tmp/raw1proc.sh

echo "\nRawPOSIX named pipes (1 process)"
echo "\nVarying write and read buffers"
python3 gen_raw1.py -w x -r x -c $1

echo -e "\nVarying write buffers"
python3 gen_raw1.py -w x -r 16 -c $1

echo -e "\nVarying read buffers"
python3 gen_raw1.py -w 16 -r x -c $1


echo "\nRawPOSIX named pipes (2 process)"
echo "\nVarying write and read buffers"
python3 gen_rawnamedpp2.py -w x -r x -c $1

echo -e "\nVarying write buffers"
python3 gen_rawnamedpp2.py -w x -r 16 -c $1

echo -e "\nVarying read buffers"
python3 gen_rawnamedpp2.py -w 16 -r x -c $1
