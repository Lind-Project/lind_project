#!/bin/bash

total_runs=50
total_time=0

for i in $(seq 1 $total_runs)
do
    output=$(./tproc) 
    avg_time=$(echo $output | grep -oP '(?<=average time )[0-9]+')
    
    total_time=$((total_time + avg_time))
    echo "Run $i: $avg_time ns"
done

average=$((total_time / total_runs))
echo "Average time over $total_runs runs: $average ns"