#!/bin/bash
for test in $(cat $1)
do
    echo "Test: $test"    
    for COUNT in $( seq 1 $2 )
    do
        # generate perf report for the test
        perf record -F 999 -a --call-graph dwarf -- lind /bin/bash /pipeline_tests/$test &> times.txt
        perf report > report.txt

        # grep read calls
        IOREAD=$(grep readat report.txt | sort -k2 -nr | head -1 | tr -dc '[. [:digit:]]' | awk '{ print $1 }')
        PIPEREAD=$(grep read_from_pipe report.txt | sort -k2 -nr | head -1 | tr -dc '[. [:digit:]]' | awk '{ print $1 }')
        # grep write calls
        IOWRITE=$(grep writeat report.txt | sort -k2 -nr | head -1 | tr -dc '[. [:digit:]]' | awk '{ print $1 }')
        PIPEWRITE=$(grep write_to_pipe report.txt | sort -k2 -nr | head -1 | tr -dc '[. [:digit:]]' | awk '{ print $1 }')
        if [[ $IOREAD ]]; then
            echo $IOREAD
        else
            echo "0"
        fi
        if [[ $PIPEWRITE ]]; then
            echo $PIPEWRITE
        else
            echo "0"
        fi
        if [[ $PIPEREAD ]]; then
            echo $PIPEREAD
        else
            echo "0"
        fi
        if [[ $IOWRITE ]]; then
            echo $IOWRITE
        else
            echo "0"
        fi
    done
done
