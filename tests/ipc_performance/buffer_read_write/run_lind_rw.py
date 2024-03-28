import argparse
import json

from subprocess import Popen, PIPE

parser = argparse.ArgumentParser(
    description="Script to benchmark sending n GBs across Lind's unix domain socket implementation with varying buffersize"
)
parser.add_argument(
    "-c", "--count", dest="count", type=int, default=10, help="Number of runs"
)
parser.add_argument(
    "-t", "--total", dest="total", type=int, default="1", help="Total size in GBs"
)
args = parser.parse_args()

run_times = {}

for size in range(8, 17, 2):
    buffer_size = str(size)
    total_time = 0
    rw_time = 0
    print(f"Buffer: {buffer_size}")
    for _ in range(args.count):
        output = Popen(
            ["lind", "/buffer_read_write_times", buffer_size, str(args.total)],
            stdout=PIPE,
            stderr=PIPE,
        )
        stdout, stderr = output.communicate()
        try:
            total, rw, _ = stdout.decode().split("\n")
            total_time += int(float(total.split()[-1]) * 1000)
            rw_time += int(float(rw.split()[-1]) * 1000)
        except ValueError:
            continue
    run_times[size] = (
        round((total_time / args.count), 1),
        round((rw_time / args.count), 1),
    )
    print(f"Runtime: {run_times[size][0]}")
    print(f"Read/Write time: {run_times[size][1]}")

with open(f"data/lind_times.json", "w") as fp:
    json.dump(run_times, fp)
