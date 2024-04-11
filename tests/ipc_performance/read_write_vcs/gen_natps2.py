import argparse
import json
from subprocess import Popen, PIPE

parser = argparse.ArgumentParser(
    description="Script to benchmark piping 16GB varying buffersize in native linux"
)
parser.add_argument(
    "-w",
    "--write-buffer",
    dest="write_buffer",
    type=str,
    default="x",
    help="Read buffer size",
)
parser.add_argument(
    "-r",
    "--read-buffer",
    dest="read_buffer",
    type=str,
    default="x",
    help="Write buffer size",
)
parser.add_argument(
    "-c", "--count", dest="count", type=int, default=10, help="Number of runs"
)
args = parser.parse_args()

run_times = {}

for size in range(2, 17):
    write_buffer_size = str(size) if args.write_buffer == "x" else args.write_buffer
    read_buffer_size = str(size) if args.read_buffer == "x" else args.read_buffer
    print(f"Write buffer: {write_buffer_size}, Read buffer: {read_buffer_size}")

    vol_ctx_switches = 0
    wall_clock_time = 0
    for _ in range(args.count):
        output = Popen(
            [
                "/bin/time",
                "-f",
                "%e wall clock, %w context switches",
                "/bin/bash",
                "ps32var2.sh",
                write_buffer_size,
                read_buffer_size,
            ],
            stdout=PIPE,
            stderr=PIPE,
            cwd="./scripts/",
        )
        stdout, stderr = output.communicate()
        print(stdout)
        print(stderr)

        try:
            times = stderr.decode().split("\n")[-2].split(",")
            wall_clock_time += float(times[0].split()[0])
            vol_ctx_switches += int(times[1].split()[0])
        except IndexError:
            continue

    run_times[size] = {
        "switches": round(vol_ctx_switches / args.count, 3),
        "time": round(wall_clock_time / args.count, 3),
        "switches/time": round(vol_ctx_switches / wall_clock_time, 3),
    }

    with open(f"data/nat_{args.write_buffer}_{args.read_buffer}.json", "w") as fp:
        json.dump(run_times, fp)
