import argparse
import json

from subprocess import Popen, PIPE

parser = argparse.ArgumentParser(description="Script to benchmark coreutils pipelines")
parser.add_argument("-c", "--count", dest="count", type=int, default=10, help="Number of runs")
args = parser.parse_args()

run_times = {}

for num in [1, 2, 4, 8, 12, 16, 32]:
    run_times[num] = []
    print(f"#cat: {num}")
    for _ in range(args.count):
        output = Popen(["lind", "-t", "/bin/bash", f"/pipeline_tests/cat{num}.sh"], stdout=PIPE, stderr=PIPE)
        stdout, stderr = output.communicate()
        
        try:
            run_time = int(float(stderr.split()[-1]) * 1000)
        except ValueError:
            continue
        run_times[num].append(run_time)
    run_times[num] = sum(run_times[num]) / args.count
    print(f"Average runtime: {run_times[num]}")

with open(f"cat_lind.json", "w") as fp:
    json.dump(run_times, fp)
