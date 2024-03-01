import argparse
import json
import subprocess
import timeit

parser = argparse.ArgumentParser(
    description="Script to benchmark sending n GBs across unix domain sockets with varying buffersize in native linux"
)
parser.add_argument(
    "-c", "--count", dest="count", type=int, default=10, help="Number of runs"
)
args = parser.parse_args()


def execute_script():
    _ = subprocess.call(["./poll_inet_tcp"], cwd="./scripts/")


run_times = {}

for size in range(1):
    run_times[size] = timeit.timeit(
        f"execute_script()",
        setup="from __main__ import execute_script",
        number=args.count,
    )
    run_times[size] = round((run_times[size] / args.count) * 1000, 1)
    print(f"Average runtime: {run_times[size]}")

with open(f"data/native.json", "w") as fp:
    json.dump(run_times, fp)
