import argparse
import json
import subprocess
import timeit

parser = argparse.ArgumentParser(
    description="Script to benchmark runtimes of coreutils pipelines in native linux"
)
parser.add_argument(
    "-c", "--count", dest="count", type=int, default=10, help="Number of runs"
)
args = parser.parse_args()

test_files = []
with open("tests.txt", "r") as f:
    test_files = [tf.strip() for tf in f.readlines() if len(tf.strip()) > 0]


def execute_script(test_file):
    _ = subprocess.call(["/bin/bash", test_file], cwd="./")


run_times = {}
for test_file in test_files:
    with open("scripts/" + test_file, "r") as f:
        print(f"Test: {f.read().strip()}")

    test = " | ".join(test_file.replace(".sh", "").split("_"))
    run_times[test] = timeit.timeit(
        f'execute_script("scripts/{test_file}")',
        setup="from __main__ import execute_script",
        number=args.count,
    )
    run_times[test] = round((run_times[test] / args.count) * 1000, 1)
    print(f"Average runtime: {run_times[test]}\n")

with open("data/native_pipelines.json", "w") as f:
    json.dump(run_times, f)
