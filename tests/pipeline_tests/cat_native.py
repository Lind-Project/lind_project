import argparse
import json
import subprocess
import timeit

parser = argparse.ArgumentParser(description="Script to benchmark coreutils pipelines")
parser.add_argument("-c", "--count", dest="count", type=int, default=10, help="Number of runs")
args = parser.parse_args()

def execute_script(num):
    process = subprocess.call(["/bin/bash", f"cat{num}.sh"])

run_times = {}

for num in [1, 2, 4, 8, 12, 16, 32]:
    run_times[num] = []
    print(f"#cat: {num}")
    run_times[num] = timeit.timeit(f"execute_script(\"{num}\")", setup="from __main__ import execute_script", number=args.count)
    run_times[num] = round((run_times[num] / args.count) * 1000, 1)
    print(f"Average runtime: {run_times[num]}")

with open(f"cat_native.json", "w") as fp:
    json.dump(run_times, fp)
