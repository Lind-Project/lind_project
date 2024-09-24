#!/bin/bash

# Compile binaries
./compile.sh

mkdir data/ 
mkdir outputs/

#####################################################################################

# echo "SFI test -- write()"

# echo "----- native -----"
# scripts/write 1 > outputs/nat_1_write.txt
# scripts/write 16 > outputs/nat_16_write.txt
# scripts/write 256 > outputs/nat_256_write.txt
# scripts/write 4096 > outputs/nat_4096_write.txt
# scripts/write 65536 > outputs/nat_65536_write.txt
# echo "----- lind -----"
# lind /write.nexe 1 > outputs/lind_1_write.txt
# lind /write.nexe 16 > outputs/lind_16_write.txt
# lind /write.nexe 256 > outputs/lind_256_write.txt
# lind /write.nexe 4096 > outputs/lind_4096_write.txt
# lind /write.nexe 65536 > outputs/lind_65536_write.txt

# echo '{' > data/write_times.json

# # Lind
# echo '  "lind": {' >> data/write_times.json
# for file in outputs/lind_*_write.txt
# do
#     buffer_size=$(tail -n 1 "$file" | awk '{print $3}')
#     avg_time=$(tail -n 1 "$file" | awk '{print $9}')
#     echo "    \"$buffer_size\": $avg_time," >> data/write_times.json
# done
# # Remove last
# sed -i '$ s/,$//' data/write_times.json
# echo '  },' >>data/ write_times.json

# # Native
# echo '  "native": {' >> data/write_times.json
# for file in outputs/nat_*_write.txt
# do
#     buffer_size=$(tail -n 1 "$file" | awk '{print $3}')
#     avg_time=$(tail -n 1 "$file" | awk '{print $9}')
#     echo "    \"$buffer_size\": $avg_time," >> data/write_times.json
# done
# # Remove
# sed -i '$ s/,$//' data/write_times.json
# echo '  }' >> data/write_times.json

# echo '}' >> data/write_times.json

#####################################################################################

echo "SFI test -- close()"

# Initialization
echo '{' > data/close_result.json
close_native_times=()
close_lind_times=()

for ((i=1; i<=$1; i++))
do
    echo "----- native -----"
    native_close_output=$(scripts/close | grep 'average time' | awk '{print $5}')
    close_native_times+=($native_close_output)
    echo "----- lind -----"
    lind_close_output=$(lind /close.nexe | grep 'average time' | awk '{print $5}')
    close_lind_times+=($lind_close_output)
done

# Write results to json file
echo '  "native": [' >> data/close_result.json
for time in "${close_native_times[@]}"
do
    echo "    $time," >> data/close_result.json
done
echo '  ],' >> data/close_result.json

echo '  "lind": [' >> data/close_result.json
for time in "${close_lind_times[@]}"
do
    echo "    $time," >> data/close_result.json
done
echo '  ],' >> data/close_result.json

#####################################################################################

echo "SFI test -- getpid()"

echo '{' > data/close_result.json
getpid_native_times=()
getpid_lind_times=()
for ((i=1; i<=$1; i++))
do
    echo "----- native -----"
    native_getpid_output=$(scripts/getpid | grep 'average time' | awk '{print $5}')
    getpid_native_times+=($native_getpid_output)
    echo "----- lind -----"
    lind_getpid_output=$(lind /getpid.nexe | grep 'average time' | awk '{print $5}')
    close_getpid_times+=($lind_getpid_output)
done

# Write results to json file
echo '  "native": [' >> data/getpid_result.json
for time in "${getpid_native_times[@]}"
do
    echo "    $time," >> data/getpid_result.json
done
echo '  ],' >> data/getpid_result.json

echo '  "lind": [' >> data/getpid_result.json
for time in "${getpid_lind_times[@]}"
do
    echo "    $time," >> data/getpid_result.json
done
echo '  ],' >> data/getpid_result.json