#!/bin/bash

mkdir -p data/
./compile.sh

echo "Running on lind stack"
./run_sysbar_lind.sh $1

echo -e "\nRunning on native linux"
./run_sysbar_native.sh $1

echo -e "\nCollecting stats"
python3 stats_collector.py data/sysbar_native_n_n data/sysbar_lind_n_n data/sysbar_n_n.json
python3 stats_collector.py data/sysbar_native_n_16 data/sysbar_lind_n_16 data/sysbar_n_16.json
python3 stats_collector.py data/sysbar_native_16_n data/sysbar_lind_16_n data/sysbar_16_n.json

echo -e "\nCleaning up"
./cleanup.sh
