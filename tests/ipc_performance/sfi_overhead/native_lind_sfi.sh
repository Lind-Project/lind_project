#!/bin/bash

echo "SFI test -- close()"

# Initialization
echo '{' > data/close_result.json
close_native_times=()
close_lind_times=()

for ((i=1; i<=$1; i++)); do
    echo "----- lind -----"
    lind_close_output=$(lind /close.nexe | grep 'average time' | awk '{print $6}')
    close_lind_times+=($lind_close_output)
done

# Write results to json file
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
    echo "----- lind -----"
    lind_getpid_output=$(lind /getpid.nexe | grep 'average time' | awk '{print $6}')
    getpid_lind_times+=($lind_getpid_output)
done

# Write results to json file
echo '  "lind": [' >> data/getpid_result.json
for time in "${getpid_lind_times[@]}"; do
    echo "    $time," >> data/getpid_result.json
done
echo '  ],' >> data/getpid_result.json
echo '}' >> data/getpid_result.json
