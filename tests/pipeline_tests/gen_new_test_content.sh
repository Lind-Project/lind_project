#!/bin/bash

let count=$(($1/5))

# Loop to create 32 different .txt files
for i in $(seq 1 32); do
    output_file="test_content/${2}_$i.txt"
    
    cat /dev/null > $output_file
    
    for c in  $( seq 1 $count ); do
        dd if=test_content/big.txt of=$output_file bs=5M count=1 oflag=append conv=notrunc
    done
    
    cat $output_file | grep -Eo '[+-]?[0-9]+([.][0-9]+)?' > "test_content/nums_$i.txt"
done
