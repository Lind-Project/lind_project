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

    ##queries
    queriesoutput="${output_file}.json"

    echo -e "\n --------------Start running queries and Save to $queriesoutput--------------\n"

    echo "{" > $queriesoutput

    for power in {16..26..2}; do
        echo "  \"$power\": [" >> $queriesoutput

        for ((i=1; i<=iterations; i++)); do
            # Execute wrk
            output=$(wrk -t1 -c1 -d${duration} --timeout 90 http://localhost:80/queries?power=$power)
            echo "executing: wrk -t1 -c1 -d${duration} --timeout 90 http://localhost:80/queries?power=$power"
            # Get Transfer/sec
            reqs_sec=$(echo "$output" | grep "Transfer/sec" | awk '{print $2}')
            
            echo "    $reqs_sec" >> $queriesoutput

            # Add ",", not add if it's last one
            if [ $i -lt 10 ]; then
                echo "," >> $queriesoutput
            fi
        done

        # End each label
        echo "  ]" >> $queriesoutput
        if [ $power -lt 26 ]; then
            echo "," >> $queriesoutput
        fi
    done

    echo "}" >> $queriesoutput

    echo "Queries Results saved to $queriesoutput"
}

if [[ "$platform" == "lind" ]]; then
    echo "================================ Running Lind Queries ================================"
    run_wrk "data/lind_queries"
else
    echo "================================ Running Native Queries ================================"
    run_wrk "data/nat_queries"
fi