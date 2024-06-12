#!/bin/bash

echo "Copying scripts to lindfs"
# lindfs cp /home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/ps16var2.sh /ps16var2.sh
# lindfs cp /home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/write16var.nexe /write16var
# lindfs cp /home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/read16var.nexe /read16var
# lindfs cp /home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/ps32var2.sh /ps32var2.sh
# lindfs cp /home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/write32var.nexe /write32var
# lindfs cp /home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/read32var.nexe /read32var
cp /home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/ps16var2.sh /home/lind/lind_project/src/safeposix-rust/tmp/ps16var2.sh
cp /home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/write16var.nexe /home/lind/lind_project/src/safeposix-rust/tmp/write16var
cp /home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/read16var.nexe /home/lind/lind_project/src/safeposix-rust/tmp/read16var
cp /home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/ps32var2.sh /home/lind/lind_project/src/safeposix-rust/tmp/ps32var2.sh
cp /home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/write32var.nexe /home/lind/lind_project/src/safeposix-rust/tmp/write32var
cp /home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/read32var.nexe /home/lind/lind_project/src/safeposix-rust/tmp/read32var

echo "Varying write and read buffers"
python3 gen_lindps2.py -w x -r x -c $1

echo -e "\nVarying write buffers"
python3 gen_lindps2.py -w x -r 16 -c $1

echo -e "\nVarying read buffers"
python3 gen_lindps2.py -w 16 -r x -c $1
