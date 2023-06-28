#!/bin/bash

let count=$(($1/5))

cat /dev/null > test_content/$2
for c in  $( seq 1 $count );
do
    dd if=test_content/big.txt of=test_content/$2 bs=5M count=1 oflag=append conv=notrunc
done
