#!/bin/bash

echo "Loading files into file system of lind and rawposix"
lindfs cp /home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/pipescript.sh /scripts/pipescript.sh
lindfs cp /home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/writepipe.nexe /scripts/writepipe
lindfs cp /home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/readpipe.nexe /scripts/readpipe

echo -e "\nLoading files into native desired location"
cp scripts/readpipe .
cp scripts/writepipe .

# cp /home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/readpipe.nexe /home/lind/lind_project/src/safeposix-rust/tmp/writepipe
# cp /home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/readpipe.nexe /home/lind/lind_project/src/safeposix-rust/tmp/readpipe

# platforms=("lind" "native" "rawposix" "unsafe")
platforms=("lind /bin/bash /scripts/pipescript.sh" "/bin/bash scripts/pipescript.sh" "scripts/unsafe-pipe")
count=$1

for platform in "${platforms[@]}"; do
    echo -e "\nRunning with: -p $platform -w 16 -r x -c $count"
    python3 gen_runtimes_plots.py -w 16 -r x -p "$platform" -c "$count"

    echo -e "\nRunning with: -p $platform -w x -r x -c $count"
    python3 gen_runtimes_plots.py -w x -r x -p "$platform" -c "$count"

    echo -e "\nRunning with: -p $platform -w x -r 16 -c $count"
    python3 gen_runtimes_plots.py -w x -r 16 -p "$platform" -c "$count"
done