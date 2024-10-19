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

    ##plaintext

    plainoutput="${output_file}_plaintext.json"
    echo -e "\n --------------Start running plaintext and Save to $plainoutput--------------\n"

    echo "{" >> $plainoutput

    for power in {16..26..2}; do
        echo "  \"$power\": [" >> $plainoutput

        for ((i=1; i<=iterations; i++)); do
            # Execute wrk
            output=$(wrk -t1 -c1 -d${duration} --timeout 30 http://localhost:80/plaintext?power=$power)
            echo "executing: wrk -t1 -c1 -d${duration} --timeout 30 http://localhost:80/plaintext?power=$power"
            # Get Transfer/sec
            reqs_sec=$(echo "$output" | grep "Transfer/sec" | awk '{print $2}')
            
            echo "    $reqs_sec" >> $plainoutput

            # Add ",", not add if it's last one
            if [ $i -lt 10 ]; then
                echo "," >> $plainoutput
            fi
        done

        # End each label
        echo "  ]" >> $plainoutput
        if [ $power -lt 26 ]; then
            echo "," >> $plainoutput
        fi
    done

    echo "}" >> $plainoutput

    echo "Plaintext Results saved to $plainoutput"


    ##queries
    queriesoutput="${output_file}_queries.json"

    echo -e "\n --------------Start running queries and Save to $queriesoutput--------------\n"

    echo "{" > $queriesoutput

    for power in {16..26..2}; do
        echo "  \"$power\": [" >> $queriesoutput

        for ((i=1; i<=iterations; i++)); do
            # Execute wrk
            output=$(wrk -t1 -c1 -d${duration} --timeout 30 http://localhost:80/queries?power=$power)
            echo "executing: wrk -t1 -c1 -d${duration} --timeout 30 http://localhost:80/queries?power=$power"
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

    echo "Plaintext Results saved to $queriesoutput"


    ##mixed

    mixedoutput="${output_file}_mixed.json"

    echo -e "\n --------------Start running mixed and Save to $mixedoutput--------------\n"

    echo "{" > $mixedoutput

    for power in {16..26..2}; do
        echo "  \"$power\": [" >> $mixedoutput

        for ((i=1; i<=iterations; i++)); do
            # Execute wrk
            output=$(wrk -t1 -c1 -d${duration} --timeout 30 http://localhost:80/mixed?power=$power)
            echo "executing: wrk -t1 -c1 -d${duration} --timeout 30 http://localhost:80/mixed?power=$power"
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
    echo "================================ Running Lind Mixed LAMP ================================"
    run_wrk "data/lind_lamp"
else
    echo "================================ Running Native Mixed LAMP ================================"
    run_wrk "data/nat_lamp"
fi