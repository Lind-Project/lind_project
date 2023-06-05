import argparse
import json
import subprocess
import timeit

parser = argparse.ArgumentParser(description="Script to benchmark piping 16GB varying buffersize in native linux")
parser.add_argument("-w", "--write-buffer", dest="write_buffer", type=str, default="x", help="Read buffer size")
parser.add_argument("-r", "--read-buffer", dest="read_buffer", type=str, default="x", help="Write buffer size")
parser.add_argument("-c", "--count", dest="count", type=int, default=10, help="Number of runs")
args = parser.parse_args()

def execute_script(write_buffer_size, read_buffer_size):
    process = subprocess.call(["cd", "scripts/", ";", "/bin/bash", "ps16var2", write_buffer_size, read_buffer_size])

run_times = {}

for size in range(4, 17, 2):
    write_buffer_size = str(size) if args.write_buffer == "x" else args.write_buffer
    read_buffer_size = str(size) if args.read_buffer == "x" else args.read_buffer
    print(f"Write buffer: {write_buffer_size}, Read buffer: {read_buffer_size}")
    run_times[size] = timeit.timeit(f"execute_script(\"{write_buffer_size}\", \"{read_buffer_size}\")", setup="from __main__ import execute_script", number=args.count)
    run_times[size] = round((run_times[size] / args.count) * 1000, 1)
    print(f"Average runtime: {run_times[size]}")

with open(f"data/nat_{args.write_buffer}_{args.read_buffer}.json", "w") as fp:
    json.dump(run_times, fp)

