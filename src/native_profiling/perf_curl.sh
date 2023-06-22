#!/bin/bash

# Setting up the LAMP stack
./setup.sh
sleep 5

# Running benchmarks
perf record -F 99 -a -o curl_perf.data --call-graph dwarf -- curl -s -o /dev/null  http://127.0.0.1
#curl -s -o /dev/null http://127.0.0.1

# Killing the LAMP stack
pkill nginx
pkill python
pkill postgres

perf report -i curl_perf.data > curl_perf.report
python3 parser.py curl_perf.report > stats
cat stats
