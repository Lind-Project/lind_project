#!/bin/bash

if [ "$2" = "native" ]; then
    echo -e "Loading files into native desired location\n"
    cp scripts/readpipe .
    cp scripts/writepipe .
    platforms=("/bin/bash scripts/pipescript.sh")
elif [ "$2" = "lind" ]; then
    echo -e "Loading files into file system of Lind\n"
    # lind will require /scripts/readpipe to execute
    lindfs cp /home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/pipescript.sh /pipescript.sh
    lindfs cp /home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/writepipe.nexe /writepipe
    lindfs cp /home/lind/lind_project/tests/ipc_performance/total_runtime/scripts/readpipe.nexe /readpipe
    platforms=("lind /bin/bash /pipescript.sh")
else
    echo "Usage: ./run_pipe_performance.sh [count] [platform]"
    exit 1
fi

count=$1

echo -e "\nRunning with: -p $platform -w 16 -r x -c $count"
python3 gen_pipedata.py -w 16 -r x -p "$platform" -c "$count"

echo -e "\nRunning with: -p $platform -w x -r x -c $count"
python3 gen_pipedata.py -w x -r x -p "$platform" -c "$count"

echo -e "\nRunning with: -p $platform -w x -r 16 -c $count"
python3 gen_pipedata.py -w x -r 16 -p "$platform" -c "$count"
