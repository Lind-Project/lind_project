import argparse
import json
import re

from subprocess import Popen, PIPE

parser = argparse.ArgumentParser(
    description="Script to benchmark context times in native"
)
parser.add_argument(
    "-f",
    "--file",
    dest="file",
    type=str,
    default="tests.txt",
    help="File with all the tests along with arguments",
)
parser.add_argument(
    "-c", "--count", dest="count", type=int, default=10, help="Number of runs"
)
args = parser.parse_args()

run_times = {}

tests = []
with open(args.file, "r") as f:
    tests = f.readlines()

for test in tests:
    test = test.strip().split()
    test_name, test_args = test[0], test[1:]
    print("Running test:", test_name, *test_args)
    test_times = []
    for _ in range(args.count):
        output = Popen([f"./scripts/{test_name}", *test_args], stdout=PIPE, stderr=PIPE)
        stdout, stderr = output.communicate()
        try:
            run_time = int(re.findall(r"time (\d+)", stdout.decode())[0])
        except IndexError:
            continue
        test_times.append(run_time)
    if len(test_times):
        run_times[test_name] = {
            "avg": round(sum(test_times) / len(test_times), 1),
            "max": max(test_times),
            "min": min(test_times),
        }

with open(f"data/native_times.json", "w") as f:
    json.dump(run_times, f)
