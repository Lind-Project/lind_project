#!/bin/bash

echo "Loading files into file system of lind and rawposix"
lindfs cp /home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/pipescript.sh /pipescript.sh
lindfs cp /home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/writepipe.nexe /writepipe
lindfs cp /home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/readpipe.nexe /readpipe

echo -e "\nLoading files into native desired location"
cp scripts/readpipe .
cp scripts/writepipe .

# cp /home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/readpipe.nexe /home/lind/lind_project/src/safeposix-rust/tmp/writepipe
# cp /home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/readpipe.nexe /home/lind/lind_project/src/safeposix-rust/tmp/readpipe

# platforms=("lind" "native" "rawposix" "unsafe")
platforms=("lind" "native" "unsafe")
count=$1

for platform in "${platforms[@]}"; do
    echo -e "\nRunning with: -p $platform -w 16 -r x -c $count"
    python3 gen_runtimes_plots.py -w 16 -r x -p "$platform" -c "$count"

    echo -e "\nRunning with: -p $platform -w x -r x -c $count"
    python3 gen_runtimes_plots.py -w x -r x -p "$platform" -c "$count"

    echo -e "\nRunning with: -p $platform -w x -r 16 -c $count"
    python3 gen_runtimes_plots.py -w x -r 16 -p "$platform" -c "$count"
done