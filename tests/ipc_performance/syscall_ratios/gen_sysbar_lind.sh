#!/bin/bash

for SIZE in {4..16..2}
do
    for COUNT in $( seq 0 $2 )
    do
        if [[ "$1" == "w" ]]; then
            SIZE1=16
            SIZE2=$SIZE
            elif [[ "$1" == "r" ]]; then
            SIZE1=$SIZE
            SIZE2=16
        else
            SIZE1=$SIZE
            SIZE2=$SIZE
        fi
        
        perf record -F 999 -a --call-graph dwarf -- lind /bin/bash pstime2.sh $SIZE1 $SIZE2 &> times.txt
        perf report > report.txt
        
        echo "$SIZE1-$SIZE2 (write)"
        grep write times.txt | tr -dc '[. [:digit:]]' | awk '{ print $2 }'
        grep NaClSysWrite report.txt | tr -dc '[. [:digit:] \n]' | awk '{ print $1 }' | sort -gr | head -n 1
        grep write_syscall report.txt | tr -dc '[. [:digit:] \n]' | awk '{ print $1 }' | sort -gr | head -n 1
        grep "write_to_pipe" report.txt | tr -dc '[. [:digit:] \n]' | awk '{ print $1 }' | sort -gr | head -n 1
        grep push_copy report.txt | tr -dc '[. [:digit:] \n]' | awk '{ print $1 }' | sort -gr | head -n 1
        
        echo "$SIZE1-$SIZE2 (read)"
        grep read times.txt | tr -dc '[. [:digit:]]' | awk '{ print $2 }'
        grep NaClSysRead report.txt | tr -dc '[. [:digit:] \n]' | awk '{ print $1 }' | sort -gr | head -n 1
        grep read_syscall report.txt | tr -dc '[. [:digit:] \n]' | awk '{ print $1 }' | sort -gr | head -n 1
        grep "read_from_pipe" report.txt | tr -dc '[. [:digit:] \n]' | awk '{ print $1 }' | sort -gr | head -n 1
        grep pop_copy report.txt | tr -dc '[. [:digit:] \n]' | awk '{ print $1 }' | sort -gr | head -n 1
        
    done
done
