#!/bin/bash

echo "Compile"
x86_64-nacl-gcc scripts/readnamed.c -o /home/lind/lind_project/src/safeposix-rust/tmp/readnamed.nexe -std=gnu99 -lpthread -O3
x86_64-nacl-gcc scripts/writenamed.c -o /home/lind/lind_project/src/safeposix-rust/tmp/writenamed.nexe -std=gnu99 -lpthread -O3

echo "Copying scripts to lindfs"
cp /home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/namedsingle.sh /home/lind/lind_project/src/safeposix-rust/tmp/namedsingle.sh
cp /home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/namedmulti.sh /home/lind/lind_project/src/safeposix-rust/tmp/namedmulti.sh

echo -e "\nRawPOSIX named pipes (Single process)"
echo -e "\nVarying write and read buffers"
python3 gen_named.py -p "/bin/bash scripts/namedsingle.sh" -w x -r x -c $1

echo -e "\nVarying write buffers"
python3 gen_named.py -p "/bin/bash scripts/namedsingle.sh" -w x -r 16 -c $1

echo -e "\nVarying read buffers"
python3 gen_named.py -p "/bin/bash scripts/namedsingle.sh" -w 16 -r x -c $1


echo -e "\nRawPOSIX named pipes (Multiple process)"
echo -e "\nVarying write and read buffers"
python3 gen_named.py -p "/bin/bash scripts/namedmulti.sh" -w x -r x -c $1

echo -e "\nVarying write buffers"
python3 gen_named.py -p "/bin/bash scripts/namedmulti.sh" -w x -r 16 -c $1

echo -e "\nVarying read buffers"
python3 gen_named.py -p "/bin/bash scripts/namedmulti.sh" -w 16 -r x -c $1
