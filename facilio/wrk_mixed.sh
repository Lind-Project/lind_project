#!/bin/bash

if [ -z "$1" ] || [ -z "$2" ] || [ -z "$3" ]; then
    echo "Usage: $0 <number_of_iterations> <duration> <platform>"
    exit 1
fi

mkdir data/

iterations=$1
duration=$2
platform=$3

# Plaintext wrk runtime function
run_wrk() {
    local output_file=$1

    ##mixed

    mixedoutput="${output_file}.json"

    echo -e "\n --------------Start running mixed and Save to $mixedoutput--------------\n"

    echo "{" > $mixedoutput

    for power in {16..26..2}; do
        echo "  \"$power\": [" >> $mixedoutput

        for ((i=1; i<=iterations; i++)); do
            # Execute wrk
            output=$(wrk -t1 -c1 -d${duration} --timeout 90 http://localhost:80/mixed?power=$power)
            echo "executing: wrk -t1 -c1 -d${duration} --timeout 90 http://localhost:80/mixed?power=$power"
            # Get Transfer/sec
            reqs_sec=$(echo "$output" | grep "Transfer/sec" | awk '{print $2}')
            
            echo "    $reqs_sec" >> $mixedoutput

            # Add ",", not add if it's last one
            if [ $i -lt 10 ]; then
                echo "," >> $mixedoutput
            fi
        done

        # End each label
        echo "  ]" >> $mixedoutput
        if [ $power -lt 26 ]; then
            echo "," >> $mixedoutput
        fi
    done

    echo "}" >> $mixedoutput

    echo "Mixed Results saved to $mixedoutput"
}

if [[ "$platform" == "lind" ]]; then
    echo "================================ Running Lind Mixed ================================"
    run_wrk "data/lind_mixed"
else
    echo "================================ Running Native Mixed ================================"
    run_wrk "data/nat_mixed"
fi