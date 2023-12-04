#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <command>"
    exit 1
fi

COMMAND=$1

max_time=0
min_time=-1
max_speed=0
min_speed=-1
total_time=0
total_speed=0

for i in {1..1073741824}
do
    # Run
    output=$($COMMAND)

    # Get time
    time=$(echo $output | grep -oP ' time \K\d+')
    speed=$(echo $output | grep -oP 'average speed \K\d+')

    # Calculate max and min
    if [ "$time" -gt "$max_time" ]; then
        max_time=$time
    fi

    if [ "$min_time" -eq "-1" ] || [ "$time" -lt "$min_time" ]; then
        min_time=$time
    fi

    if [ "$speed" -gt "$max_speed" ]; then
        max_speed=$speed
    fi

    if [ "$min_speed" -eq "-1" ] || [ "$speed" -lt "$min_speed" ]; then
        min_speed=$speed
    fi

    total_speed=$((total_speed + speed))

    total_time=$((total_time + time))
done

# Calculate average
average_time=$((total_time / 1073741824))
average_speed=$((total_speed / 1073741824))

# Output
echo "Max Time: $max_time ns"
echo "Min Time: $min_time ns"
echo "Average Time: $average_time ns"
echo "Max Speed: $max_speed ns"
echo "Min Speed: $min_speed ns"
echo "Average Time: $average_speed ns"
