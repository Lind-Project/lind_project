#!/bin/bash

if [ "$2" = "raw" ]; then
    echo "Loading files into rawposix"
    lindfs cp /home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/pipescript.sh /home/lind/lind_project/src/safeposix-rust/tmp/pipescript.sh
    cp /home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/readpipe.nexe /home/lind/lind_project/src/safeposix-rust/tmp/writepipe
    cp /home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/readpipe.nexe /home/lind/lind_project/src/safeposix-rust/tmp/readpipe
    platforms=("rawposix")
elif [ "$2" = "other" ]; then
    echo "Loading files into file system of lind"
    lindfs cp /home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/pipescript.sh /pipescript.sh
    lindfs cp /home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/writepipe.nexe /writepipe
    lindfs cp /home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/readpipe.nexe /readpipe
    echo -e "\nLoading files into native desired location"
    # lind will require /scripts/readpipe to execute
    cp scripts/readpipe .
    cp scripts/writepipe .
    platforms=("lind /bin/bash /pipescript.sh" "/bin/bash scripts/pipescript.sh" "scripts/unsafe-pipe")
else
    echo "Usage: ./run_pipe_performance.sh [count] [platform]"
    exit 1
fi

count=$1

for platform in "${platforms[@]}"; do
    echo -e "\nRunning with: -p $platform -w 16 -r x -c $count"
    python3 gen_pipedata.py -w 16 -r x -p "$platform" -c "$count"

    echo -e "\nRunning with: -p $platform -w x -r x -c $count"
    python3 gen_pipedata.py -w x -r x -p "$platform" -c "$count"

    echo -e "\nRunning with: -p $platform -w x -r 16 -c $count"
    python3 gen_pipedata.py -w x -r 16 -p "$platform" -c "$count"
done