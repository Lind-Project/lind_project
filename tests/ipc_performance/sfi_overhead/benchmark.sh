#!/bin/bash

# Compile binaries
./compile.sh

mkdir data/ 
mkdir outputs/

#####################################################################################
# ------
# Use RustPOSIX + libc-write
./rustposix_fast.sh
# ------

echo "SFI test -- write()"

nat_command="scripts/write"
lind_command="lind /write.nexe"
output_dir="outputs"

# Run write() test and then put the output into JSON file
function run_tests() {
    local command=$1
    local buffer_size=$2
    local platform=$3
    local output_file="${output_dir}/${platform}_${buffer_size}_write.txt"
    total_avg_time=0
    local iterations_count=${iterations[$buffer_size]} 
    # Run write() test case and extract the average runtime
    echo "Running $command $buffer_size > $output_file"
    # Run the write test for the given number of iterations
    echo "Iteration $i for buffer size $buffer_size"
    current_time=$($command $buffer_size | tail -n 1 | awk '{print $10}')
    echo "Buffer size: $buffer_size, Average time: $current_time ns"
    # Put average data into JSON file
    echo "    $current_time," >> "data/write_$platform.json"
    # Remove output file after operation
    rm -f "$output_file"
}

# Clear and initialize JSON file
function init_json() {
    local platform=$1
    echo "{" > "data/write_$platform.json"
}

# Finalize JSON
function finalize_json() {
    local platform=$1
    echo "}" >> "data/write_$platform.json"
}

echo "----- native -----"
init_json "nat"
for buf_size in 1 16 256 4096 65536; do
    echo "  \"$buf_size\": [" >> "data/write_nat.json"
    for ((i=1; i<=$1; i++)); do
        run_tests "$nat_command" $buf_size "nat"
    done
    echo '  ]' >> "data/write_nat.json"
done
finalize_json "nat"

echo "----- lind -----"
init_json "lind"
for buf_size in 1 16 256 4096 65536; do
    echo "  \"$buf_size\": [" >> "data/write_lind.json"
    for ((i=1; i<=$1; i++)); do
        run_tests "$lind_command" $buf_size "lind"
    done
    echo '  ]' >> "data/write_lind.json"
done
finalize_json "lind"

#####################################################################################
# ------
# Use regular RustPOSIX
./rustposix.sh
# ------

echo "SFI test -- close()"

# Initialization
echo '{' > data/close_result.json
close_native_times=()
close_lind_times=()

for ((i=1; i<=$1; i++)); do
    echo "----- native -----"
    native_close_output=$(scripts/close | grep 'average time' | awk '{print $6}')
    close_native_times+=($native_close_output)
    echo "----- lind -----"
    lind_close_output=$(lind /close.nexe | grep 'average time' | awk '{print $6}')
    close_lind_times+=($lind_close_output)
done

# Write results to json file
echo '  "native": [' >> data/close_result.json
for time in "${close_native_times[@]}"; do
    echo "    $time," >> data/close_result.json
done
echo '  ],' >> data/close_result.json

echo '  "lind": [' >> data/close_result.json
for time in "${close_lind_times[@]}";  do
    echo "    $time," >> data/close_result.json
done
echo '  ]' >> data/close_result.json
echo '}' >> data/close_result.json
#####################################################################################

echo "SFI test -- getpid()"

echo '{' > data/getpid_result.json
getpid_native_times=()
getpid_lind_times=()
for ((i=1; i<=$1; i++)); do
    echo "----- native -----"
    native_getpid_output=$(scripts/getpid | grep 'average time' | awk '{print $6}')
    getpid_native_times+=($native_getpid_output)
    echo "----- lind -----"
    lind_getpid_output=$(lind /getpid.nexe | grep 'average time' | awk '{print $6}')
    getpid_lind_times+=($lind_getpid_output)
done

# Write results to json file
echo '  "native": [' >> data/getpid_result.json
for time in "${getpid_native_times[@]}"; do
    echo "    $time," >> data/getpid_result.json
done
echo '  ],' >> data/getpid_result.json

echo '  "lind": [' >> data/getpid_result.json
for time in "${getpid_lind_times[@]}"; do
    echo "    $time," >> data/getpid_result.json
done
echo '  ],' >> data/getpid_result.json
echo '}' >> data/getpid_result.json
