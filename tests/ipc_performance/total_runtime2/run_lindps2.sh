#!/bin/bash

echo "Copying scripts to lindfs"
lindfs cp /home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/pipescript.sh /pipescript.sh
lindfs cp /home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/writepipe.nexe /writepipe
lindfs cp /home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/readpipe.nexe /readpipe

echo "Varying write and read buffers"
python3 gen_lindps2.py -w x -r x -c $1

echo -e "\nVarying write buffers"
python3 gen_lindps2.py -w x -r 16 -c $1

echo -e "\nVarying read buffers"
python3 gen_lindps2.py -w 16 -r x -c $1
