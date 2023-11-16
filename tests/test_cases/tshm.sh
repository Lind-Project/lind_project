#!/bin/bash

total_time_native=0
total_time_lind=0
iterations=50

# Run Native
for i in $(seq 1 $iterations); do
    output=$(./tshm)
    avg_time=$(echo $output | grep -oP '\d+ shared memory calls, average time \K\d+')
    total_time_native=$((total_time_native + avg_time))
done

# Native average time
average_native=$((total_time_native / iterations))
echo "Average time for native: $average_native ns"

# Run Lind 
for i in $(seq 1 $iterations); do
    output=$(lind /tshm.nexe)
    avg_time=$(echo $output | grep -oP '\d+ shared memory calls, average time \K\d+')
    total_time_lind=$((total_time_lind + avg_time))
done

# Lind average time
average_lind=$((total_time_lind / iterations))
echo "Average time for lind: $average_lind ns"
