#!/bin/bash

cd scripts/
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
        
        perf record -F 999 -a --call-graph dwarf -- /bin/bash pstime2.sh $SIZE1 $SIZE2 &> times.txt
        perf report > report.txt
        
        echo "$SIZE1-$SIZE2 (write)"
        grep write times.txt | tr -dc '[. [:digit:]]' | awk '{ print $2 }'
        LIBC=$(grep libc report.txt | grep write | sort -k2 -nr | head -1 | tr -dc '[. [:digit:]]' | awk '{ print $1 }')
        KSYSWRITE=$(grep ksys_write report.txt | sort -k2 -nr | head -1 | tr -dc '[. [:digit:]]' | awk '{ print $1 }')
        PIPEWRITE=$(grep pipe_write report.txt | sort -k2 -nr | head -1 | tr -dc '[. [:digit:]]' | awk '{ print $1 }')
        if [[ $LIBC ]]; then
            echo $LIBC
        else
            echo "1"
        fi
        if [[ $KSYSWRITE ]]; then
            echo $KSYSWRITE
        else
            echo "0"
        fi
        if [[ $PIPEWRITE ]]; then
            echo $PIPEWRITE
        else
            echo "0"
        fi
        
        WRITER=$(grep write_var_time report.txt | grep copy_page_from_iter | sort -k2 -nr | head -1 | tr -dc '[. [:digit:]]' | awk '{ print $1 }')
        WRUNROLL=$(grep write_var_time report.txt | grep copy_user_generic_unrolled | sort -k2 -nr | head -1 | tr -dc '[. [:digit:]]' | awk '{ print $1 }')
        WRSTRCOPY=$(grep write_var_time report.txt | grep copy_user_enhanced_fast_string | sort -k2 -nr | head -1 | tr -dc '[. [:digit:]]' | awk '{ print $1 }')
        if [[ $WRITER ]]; then
            echo $WRITER
        else
            echo "0"
        fi
        if [[ $WRUNROLL ]]; then
            echo $WRUNROLL
        else
            echo "0"
        fi
        if [[ $WRSTRCOPY ]]; then
            echo $WRSTRCOPY
        else
            echo "0"
        fi
        
        
        echo "$SIZE1-$SIZE2 (read)"
        grep read times.txt | tr -dc '[. [:digit:]]' | awk '{ print $2 }'
        LIBC=$(grep libc report.txt | grep read | sort -k2 -nr | head -1 | tr -dc '[. [:digit:]]' | awk '{ print $1 }')
        KSYSREAD=$(grep ksys_read report.txt | sort -k2 -nr | head -1 | tr -dc '[. [:digit:]]' | awk '{ print $1 }')
        PIPEREAD=$(grep pipe_read report.txt | sort -k2 -nr | head -1 | tr -dc '[. [:digit:]]' | awk '{ print $1 }')
        if [[ $LIBC ]]; then
            echo $LIBC
        else
            echo "1"
        fi
        if [[ $KSYSREAD ]]; then
            echo $KSYSREAD
        else
            echo "0"
        fi
        if [[ $PIPEREAD ]]; then
            echo $PIPEREAD
        else
            echo "0"
        fi
        
        RDITER=$(grep read_var_time report.txt | grep copy_page_to_iter | sort -k2 -nr | head -1 | tr -dc '[. [:digit:]]' | awk '{ print $1 }')
        RDUNROLL=$(grep read_var_time report.txt | grep copy_user_generic_unrolled | sort -k2 -nr | head -1 | tr -dc '[. [:digit:]]' | awk '{ print $1 }')
        RDSTRCOPY=$(grep read_var_time report.txt | grep copy_user_enhanced_fast_string | sort -k2 -nr | head -1 | tr -dc '[. [:digit:]]' | awk '{ print $1 }')
        if [[ $RDITER ]]; then
            echo $RDITER
        else
            echo "0"
        fi
        if [[ $RDUNROLL ]]; then
            echo $RDUNROLL
        else
            echo "0"
        fi
        if [[ $RDSTRCOPY ]]; then
            echo $RDSTRCOPY
        else
            echo "0"
        fi
    done
done
