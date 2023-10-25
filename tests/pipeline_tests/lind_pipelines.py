import argparse
import json
from subprocess import Popen, PIPE

parser = argparse.ArgumentParser(
    description="Script to benchmark runtimes of coreutils pipelines in lind"
)
parser.add_argument(
    "-c", "--count", dest="count", type=int, default=10, help="Number of runs"
)
args = parser.parse_args()

test_files = []
with open("tests.txt", "r") as f:
    test_files = [tf.strip() for tf in f.readlines() if len(tf.strip()) > 0]


run_times = {}
for test_file in test_files:
    with open("scripts/" + test_file, "r") as f:
        print(f"Test: {f.read().strip()}")

    test = " | ".join(test_file.replace(".sh", "").split("_"))
    for _ in range(args.count):
        output = Popen(["lind", "-t", "/bin/bash", test_file], stdout=PIPE, stderr=PIPE)
        stdout, stderr = output.communicate()

        try:
            run_time = int(float(stderr.split()[-1]) * 1000)
        except ValueError:
            continue
        run_times[test].append(run_time)
    run_times[test] = sum(run_times[test]) / args.count
    print(f"Average runtime: {run_times[test]}\n")

with open("data/lind_pipelines.json", "w") as f:
    json.dump(run_times, f)
