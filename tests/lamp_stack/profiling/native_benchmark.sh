#!/bin/bash

set_cols(){
    COL_NC='\e[0m' # No Color
    COL_LIGHT_GREEN='\e[1;32m'
    COL_LIGHT_RED='\e[1;31m'
    TICK="[${COL_LIGHT_GREEN}✓${COL_NC}]"
    CROSS="[${COL_LIGHT_RED}✗${COL_NC}]"
    INFO="[i]"
    DONE="${COL_LIGHT_GREEN} done!${COL_NC}"
    OVER="\\r\\033[K"
}

while [[ "$#" -gt 0 ]]; do
    case $1 in
        -t|--threads) threads="$2"; shift ;;
        -c|--connections) connections="$2"; shift ;;
	-d|--duration) duration="$2"; shift;;
	-s|--size) size="$2"; shift;;
	-n|--num-pages) num_pages="$2"; shift;;
        *) echo "Unknown parameter passed: $1"; exit 1 ;;
    esac
    shift
done

set_cols

FILE_PATH="benchmark_stats/t${threads}_c${connections}_d${duration}_s${size}_n${num_pages}"
echo $FILE_PATH

echo -e "${INFO} Configuring LAMP stack"
./setup.sh
sleep 5
echo -e "${INFO} Benchmarking the LAMP stack using perf and wrk"
perf record -F 99 -a -o lamp.perf.data --call-graph dwarf -- wrk -t$threads -c$connections -d$duration --timeout $duration http://127.0.0.1
echo -e "${TICK} LAMP stack configured and benchmarked"
sleep 5
echo -e "${INFO} Killing LAMP stack"
pkill python
pkill nginx
pkill postgres
echo -e "${TICK} LAMP stack killed"

echo -e "${INFO} Parsing perf stats"
perf report -i lamp.perf.data > lamp.perf.report
python3 parser.py lamp.perf.report > $FILE_PATH
echo -e "${TICK} Parsing completed and stats are stored in ${FODLER_PATH}/lamp.perf.stats"
cat $FILE_PATH
echo -e "${DONE}"