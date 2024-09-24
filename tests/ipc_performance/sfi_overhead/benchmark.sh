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

declare -A iterations
iterations[1]=1 #1073741824
iterations[16]=8 #134217728
iterations[256]=128 #8388608
iterations[4096]=204 #524288
iterations[65536]=32768 #32768

# Run write() test and then put the output into JSON file
function run_tests() {
    local command=$1
    local buffer_size=$2
    local platform=$3
    local output_file="${output_dir}/${platform}_${buffer_size}_write.txt"
    total_avg_time=0
    local iterations_count=${iterations[$buffer_size]} 

    # Remove previous output file
    rm -f "$output_file"

    # Run write() test case and extract the average runtime
    echo "Running $command $buffer_size > $output_file"
    # Run the write test for the given number of iterations
    for ((i=1; i<=iterations_count; i++)); do
        echo "Iteration $i for buffer size $buffer_size"
        current_time=$($command $buffer_size | tail -n 1 | awk '{print $10}')
        echo "Time for iteration $i: $current_time ns"
        total_avg_time=$(echo "$total_avg_time + $current_time" | bc)
    done

    avg_time=$(echo "$total_avg_time / $iterations_count" | bc)
    echo "Buffer size: $buffer_size, Average time: $avg_time ns"

    # Put final average data into JSON file
    echo "    \"$buffer_size\": $avg_time," >> "data/write_$platform.json"
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
  run_tests "$nat_command" $buf_size "nat"
done
finalize_json "nat"

echo "----- lind -----"
init_json "lind"
for buf_size in 1 16 256 4096 65536; do
  run_tests "$lind_command" $buf_size "lind"
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
