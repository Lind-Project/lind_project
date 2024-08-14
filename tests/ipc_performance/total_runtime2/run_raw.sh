#!/bin/bash

echo "Compile"
x86_64-nacl-gcc scripts/read.c -o /home/lind/lind_project/src/safeposix-rust/tmp/readshort.nexe -std=gnu99 -lpthread -O3
x86_64-nacl-gcc scripts/write.c -o /home/lind/lind_project/src/safeposix-rust/tmp/writeshort.nexe -std=gnu99 -lpthread -O3
x86_64-nacl-gcc scripts/short1proc.c -o /home/lind/lind_project/src/safeposix-rust/tmp/short1proc.nexe -std=gnu99 -lpthread -O3

echo "Copying scripts to lindfs"
cp /home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/raw1short.sh /home/lind/lind_project/src/safeposix-rust/tmp/raw1short.sh
cp /home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/raw2short.sh /home/lind/lind_project/src/safeposix-rust/tmp/raw2short.sh

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
