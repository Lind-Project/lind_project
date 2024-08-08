#!/bin/bash

mkdir -p data/
./compile.sh

echo -e "\nRunning on native linux"
./run_natps2.sh $1

echo -e "\nRunning on native linux 32"
./run_nat32ps2.sh $1

echo -e "\nRunning on native linux no libc"
./run_natnolibcps2.sh $1

echo -e "\nCleaning up"
./cleanup.sh
