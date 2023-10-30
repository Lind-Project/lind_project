import argparse
import json

from subprocess import Popen, PIPE

parser = argparse.ArgumentParser(description="Script to benchmark sending 1GB across Lind's unix domain socket implementation with varying buffersize")
parser.add_argument("-w", "--buffer", dest="buffer", type=str, default="x", help="Buffer size")
parser.add_argument("-c", "--count", dest="count", type=int, default=10, help="Number of runs")
args = parser.parse_args()

run_times = {}

for size in range(4, 17, 2):
    buffer_size = str(size) if args.buffer == "x" else args.buffer
    run_times[size] = []
    print(f"Buffer: {buffer_size}")
    for _ in range(args.count):
        output = Popen(["lind", "-t", "/uds", buffer_size], stdout=PIPE, stderr=PIPE)
        stdout, stderr = output.communicate()
        try:
            run_time = int(float(stderr.split()[-1]) * 1000)
        except ValueError:
            continue
        run_times[size].append(run_time)
    run_times[size] = sum(run_times[size]) / args.count
    print(f"Average runtime: {run_times[size]}")

with open(f"data/lind_{args.buffer}.json", "w") as fp:
    json.dump(run_times, fp)

