#!/bin/bash

mkdir -p data/
./compile.sh

echo "Running on lind stack"
./run_lindps2.sh $1

echo -e "\nRunning on native linux"
./run_natps2.sh $1

echo -e "\nRunning in userspace"
./run_userps2.sh $1

echo -e "\nCleaning up"
./cleanup.sh
