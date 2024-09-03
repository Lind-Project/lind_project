import argparse
import json
import subprocess
import timeit
import os
from subprocess import Popen, PIPE

parser = argparse.ArgumentParser(description="Script to benchmark coreutils pipelines")
parser.add_argument(
    "-c", "--count", dest="count", type=int, default=10, help="Number of runs"
)
args = parser.parse_args()


def generate_script(num):
    files = [f"./test_content/content_{i}.txt" for i in range(1, num + 1)]
    script = f"/bin/cat {' '.join(files)}"
    cats = ["| /bin/cat" for _ in range(num - 1)]
    script += " ".join(cats)
    script += " > cat_cat.out"
    print(script)
    with open("scripts/cat_cat.sh", "w") as f:
        f.write(script)


def execute_script():
    process = subprocess.call(["/bin/bash", f"scripts/cat_cat.sh"])


run_times = {}
lind_run_times = {}

for num in [1, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 24, 28, 32]:
    print(f"\n#cat: {num}")
    generate_script(num)

    run_times[num] = []
    run_times[num] = timeit.timeit(
        f"execute_script()",
        setup="from __main__ import execute_script",
        number=args.count,
    )
    run_times[num] = round((run_times[num] / args.count) * 1000, 1)
    print(f"Average native runtime: {run_times[num]}")

    lind_run_times[num] = []
    subprocess.call(
        [
            "lindfs",
            "cp",
            "/home/lind/lind_project/tests/pipeline_tests/scripts/cat_cat.sh",
            "/pipeline_tests/cat_cat.sh",
        ]
    )
    for _ in range(args.count):
        output = Popen(
            ["lind", "/bin/bash", "/pipeline_tests/cat_cat.sh"],
            stdout=PIPE,
            stderr=PIPE,
        )
        stdout, stderr = output.communicate()

        try:
            run_time = int(float(stderr.split()[-1]) * 1000)
        except ValueError:
            continue
        lind_run_times[num].append(run_time)
    lind_run_times[num] = sum(lind_run_times[num]) / args.count
    print(f"Average lind runtime: {lind_run_times[num]}")

with open(f"cat_native.json", "w") as fp:
    json.dump(run_times, fp)

with open(f"cat_lind.json", "w") as fp:
    json.dump(lind_run_times, fp)
