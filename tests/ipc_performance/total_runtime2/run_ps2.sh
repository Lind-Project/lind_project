#!/bin/bash

echo "Loading files into file system of lind and rawposix"
lindfs cp /home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/pipescript.sh /pipescript.sh
lindfs cp /home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/writepipe.nexe /writepipe
lindfs cp /home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/readpipe.nexe /readpipe

# cp /home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/readpipe.nexe /home/lind/lind_project/src/safeposix-rust/tmp/writepipe
# cp /home/lind/lind_project/tests/ipc_performance/total_runtime2/scripts/readpipe.nexe /home/lind/lind_project/src/safeposix-rust/tmp/readpipe

# platforms=("lind" "native" "rawposix" "unsafe")
platforms=("lind" "native" "unsafe")
write_buffer_sizes=(16 "x")
read_buffer_sizes=(16 "x")
count=5

for platform in "${platforms[@]}"; do
    for write_size in "${write_buffer_sizes[@]}"; do
        for read_size in "${read_buffer_sizes[@]}"; do
            echo "Running with -p $platform -w $write_size -r $read_size -c $count"
            python3 gen_ps2.py -w "$write_size" -r "$read_size" -p "$platform" -c "$count"
        done
    done
done