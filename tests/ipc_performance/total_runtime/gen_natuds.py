import argparse
import json
import subprocess
import timeit

parser = argparse.ArgumentParser(description="Script to benchmark sending 1GB across unix domain sockets with varying buffersize in native linux")
parser.add_argument("-b", "--buffer", dest="buffer", type=str, default="x", help="Buffer size")
parser.add_argument("-c", "--count", dest="count", type=int, default=10, help="Number of runs")
args = parser.parse_args()

def execute_script(buffer_size):
    process = subprocess.call(["./uds", buffer_size], cwd="./uds_scripts/")

run_times = {}

for size in range(4, 17, 2):
    buffer_size = str(size) if args.buffer == "x" else args.buffer
    print(f"Buffer: {buffer_size}")
    run_times[size] = timeit.timeit(f"execute_script(\"{buffer_size}\")", setup="from __main__ import execute_script", number=args.count)
    run_times[size] = round((run_times[size] / args.count) * 1000, 1)
    print(f"Average runtime: {run_times[size]}")

with open(f"data/uds/nat_{args.buffer}.json", "w") as fp:
    json.dump(run_times, fp)
