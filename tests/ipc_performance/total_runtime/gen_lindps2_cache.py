import argparse
import json
import re

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

cache_misses = {}

for size in range(1, 17):
    write_buffer_size = str(size) if args.write_buffer == "x" else args.write_buffer
    read_buffer_size = str(size) if args.read_buffer == "x" else args.read_buffer
    cache_misses[size] = []
    print(f"Write buffer: {write_buffer_size}, Read buffer: {read_buffer_size}")
    for _ in range(args.count):
        output = Popen(
            [
                "perf",
                "stat",
                "-B",
                "-e",
                "cache-misses",
                "lind",
                "/bin/bash",
                "ps32var2.sh",
                write_buffer_size,
                read_buffer_size,
            ],
            stdout=PIPE,
            stderr=PIPE,
        )
        stdout, stderr = output.communicate()
        try:
            stderr = stderr.decode()
            cache_miss = int(re.findall(r"(\d+)[ ]+cpu_core", stderr)[0])
        except ValueError:
            continue
        cache_misses[size].append(cache_miss)
    print(f"Average cache misses: {sum(cache_misses[size]) / args.count}")

    with open(f"data/lind_{args.write_buffer}_{args.read_buffer}_cache_misses_256.json", "w") as fp:
        json.dump(cache_misses, fp)
