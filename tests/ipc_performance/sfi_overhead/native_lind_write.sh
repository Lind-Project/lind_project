#!/bin/bash

mkdir data/
mkdir outputs/

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
