#!/bin/bash

echo "Copying scripts to lindfs"
lindfs cp /home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/ps16var2.sh /ps16var2.sh
lindfs cp /home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/write16var.nexe /write16var
lindfs cp /home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/read16var.nexe /read16var

echo "Varying write and read buffers"
python3 gen_lindps2.py -w x -r x -c $1

echo -e "\nVarying write buffers"
python3 gen_lindps2.py -w x -r 16 -c $1

echo -e "\nVarying read buffers"
python3 gen_lindps2.py -w 16 -r x -c $1
