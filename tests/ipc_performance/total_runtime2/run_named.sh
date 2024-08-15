#!/bin/bash

echo "Compile"
./compile.sh

echo "Copying scripts to lindfs"
cp /home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/namedsingle.sh /home/lind/lind_project/src/safeposix-rust/tmp/namedsingle.sh
cp /home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/namedmulti.sh /home/lind/lind_project/src/safeposix-rust/tmp/namedmulti.sh

echo "Check if FIFO file exists"
FIFO_PATH="/home/lind/lind_project/src/safeposix-rust/tmp/myfifo"
if [ ! -p "$FIFO_PATH" ]; then
    mkfifo "FIFO_PATH"
fi

echo -e "\nRawPOSIX named pipes (Single process)"
echo -e "\nVarying write and read buffers"
python3 gen_named.py -p "lind /bin/bash /namedsingle.sh" -w x -r x -c $1

echo -e "\nVarying write buffers"
python3 gen_named.py -p "lind /bin/bash /namedsingle.sh" -w x -r 16 -c $1

echo -e "\nVarying read buffers"
python3 gen_named.py -p "lind /bin/bash /namedsingle.sh" -w 16 -r x -c $1


echo -e "\nRawPOSIX named pipes (Multiple process)"
echo -e "\nVarying write and read buffers"
python3 gen_named.py -p "/bin/bash scripts/namedmulti.sh" -w x -r x -c $1

echo -e "\nVarying write buffers"
python3 gen_named.py -p "/bin/bash scripts/namedmulti.sh" -w x -r 16 -c $1

echo -e "\nVarying read buffers"
python3 gen_named.py -p "/bin/bash scripts/namedmulti.sh" -w 16 -r x -c $1
