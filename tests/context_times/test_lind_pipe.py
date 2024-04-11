import argparse
import json

from subprocess import Popen, PIPE

parser = argparse.ArgumentParser(
    description="Script to benchmark context pipe times in lind"
)
parser.add_argument(
    "-c", "--count", dest="count", type=int, default=10, help="Number of runs"
)
parser.add_argument(
    "-t",
    "--total-size",
    dest="total_size",
    type=int,
    default=2,
    help="Total Size in GBs",
)
args = parser.parse_args()

run_times = {}
for buf in range(16, 17, 4):
    vol_ctx_switches = 0
    wall_clock_time = 0
    for _ in range(args.count):
        output = Popen(
            [
                "/bin/time",
                "-f",
                "%e wall clock, %w context switches",
                "lind",
                "/context_pipe",
                str(buf),
                str(args.total_size),
            ],
            stdout=PIPE,
            stderr=PIPE,
        )
        stdout, stderr = output.communicate()

        try:
            times = stderr.decode().split("\n")[-2].split(",")
            wall_clock_time += float(times[0].split()[0])
            vol_ctx_switches += int(times[1].split()[0])
        except IndexError:
            continue

    run_times[buf] = {
        "switches": round(vol_ctx_switches / args.count, 3),
        "time": round(wall_clock_time / args.count, 3),
        "switches/time": round(vol_ctx_switches / wall_clock_time, 3),
    }

with open(f"data/lind_ctx_pipe_times.json", "w") as f:
    json.dump(run_times, f)
