#!/bin/bash

output_file="lind_bwpipe.json"

# Start the JSON array
echo "[" > "$output_file"

for i in $(seq 1 10); do
    latency=$(lind /bw_pipe | awk '{print $3}')

    # Add the value to the file
    if [ "$i" -lt 10 ]; then
        echo "  $latency," >> "$output_file"
    else
        echo "  $latency" >> "$output_file"
    fi
done

# End the JSON array
echo "]" >> "$output_file"

echo "Results saved to $output_file"
