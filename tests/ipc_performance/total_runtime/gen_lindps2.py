import argparse
import json

from subprocess import Popen, PIPE

parser = argparse.ArgumentParser(
    description="Script to benchmark piping 16GB varying buffersize in lind"
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

for size in range(4, 17, 1):
    write_buffer_size = str(size) if args.write_buffer == "x" else args.write_buffer
    read_buffer_size = str(size) if args.read_buffer == "x" else args.read_buffer
    run_times[size] = []
    print(f"Write buffer: {write_buffer_size}, Read buffer: {read_buffer_size}")
    for _ in range(args.count):
        output = Popen(
            [
                "lind",
                "-t",
                "/bin/bash",
                "ps16var2.sh",
                write_buffer_size,
                read_buffer_size,
            ],
            stdout=PIPE,
            stderr=PIPE,
        )
        stdout, stderr = output.communicate()

        try:
            run_time = int(float(stderr.split()[-1]) * 1000)
        except ValueError:
            continue
        run_times[size].append(run_time)
    print(f"Average runtime: {sum(run_times[size]) / args.count}")

with open(f"data/lind_{args.write_buffer}_{args.read_buffer}.json", "w") as fp:
    json.dump(run_times, fp)
