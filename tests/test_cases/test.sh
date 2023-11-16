#!/bin/bash

COMMAND="./t"

max_time=0
min_time=-1
total_time=0

for i in {1..50}
do
    # Run
    output=$($COMMAND)

    # Get time
    time=$(echo $output | grep -oP 'total time \K\d+')

    # Calculate max and min
    if [ "$time" -gt "$max_time" ]; then
        max_time=$time
    fi

    if [ "$min_time" -eq "-1" ] || [ "$time" -lt "$min_time" ]; then
        min_time=$time
    fi

    total_time=$((total_time + time))
done

# Calculate average
average_time=$((total_time / 50))

# Output
echo "Max Time: $max_time ns"
echo "Min Time: $min_time ns"
echo "Average Time: $average_time ns"
