import argparse
import json

from subprocess import Popen, PIPE

parser = argparse.ArgumentParser(description="Script to benchmark sending n GBs across Lind's unix domain socket implementation with varying buffersize")
parser.add_argument("-c", "--count", dest="count", type=int, default=10, help="Number of runs")
parser.add_argument("-t", "--total", dest="total", type=int, default="1", help="Total size in GBs")
args = parser.parse_args()

run_times = {}

for size in range(2, 17, 2):
    buffer_size = str(size)
    run_times[size] = []
    print(f"Buffer: {buffer_size}")
    for _ in range(args.count):
        output = Popen(["lind", "-t", "/buffer_read_write", buffer_size, str(args.total)], stdout=PIPE, stderr=PIPE)
        stdout, stderr = output.communicate()
        try:
            run_time = int(float(stderr.split()[-1]) * 1000)
        except ValueError:
            continue
        run_times[size].append(run_time)
    run_times[size] = sum(run_times[size]) / args.count
    print(f"Average runtime: {run_times[size]}")

with open(f"data/lind.json", "w") as fp:
    json.dump(run_times, fp)
