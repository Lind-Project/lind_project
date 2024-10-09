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
    echo -e "\n --------------Start running $platform and Save to $output_file--------------\n"

    echo "{" > $output_file

    for filesize in {17..27..2}; do
        echo "  \"$filesize\": [" >> $output_file

        for ((i=1; i<=iterations; i++)); do
            # Execute wrk according to platform
            if [[ "$platform" == "lind" ]]; then
                output=$(wrk -t1 -c1 -d${duration} --timeout 30 http://localhost:80/static_${filesize}.html)
            else
                output=$(wrk -t1 -c1 -d${duration} --timeout 30 http://localhost:80/home/lind/lind_project/static_${filesize}.html)
            fi

            # Get Requests/sec
            reqs_sec=$(echo "$output" | grep "Requests/sec" | awk '{print $2}')
            
            echo "    $reqs_sec" >> $output_file

            # Add ",", not add if it's last one
            if [ $i -lt 10 ]; then
                echo "," >> $output_file
            fi

                
        done

        # End each label
        echo "  ]" >> $output_file
        if [ $filesize -lt 26 ]; then
            echo "," >> $output_file
        fi
    done

    echo "}" >> $output_file

    echo "Results saved to $output_file"
}

if [[ "$platform" == "lind" ]]; then
    run_wrk "data/lind_ng" 
else
    run_wrk "data/nat_ng" 
fi
