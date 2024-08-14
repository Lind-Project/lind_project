import argparse
import json
import re

from subprocess import Popen, PIPE, STDOUT

def extract_times(output):
    # Extract numbers from the 'write-start' and 'read-end' lines
    write_start_match = re.search(r'write-start: (\d+)', output)
    read_end_match = re.search(r'read-end: (\d+)', output)
    if write_start_match and read_end_match:
        write_start = int(write_start_match.group(1))
        read_end = int(read_end_match.group(1))
        return (read_end - write_start) / 1000000
    else:
        return None
    
parser = argparse.ArgumentParser(
    description="Script to benchmark piping 1GB varying buffersize in lind"
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

for size in range(4, 17, 2):
    write_buffer_size = str(size) if args.write_buffer == "x" else args.write_buffer
    read_buffer_size = str(size) if args.read_buffer == "x" else args.read_buffer
    run_times[size] = []
    print(f"Write buffer: {write_buffer_size}, Read buffer: {read_buffer_size}")
    for _ in range(args.count):
        output = Popen(
            [
                "lind",
                "/bin/bash",
                "raw1short.sh",
                write_buffer_size,
                read_buffer_size,
            ],
            stdout=PIPE,
            stderr=STDOUT,
        )
        stdout, _ = output.communicate()
        stdout = stdout.decode('utf-8') # Decode bytes to string
        try:
            run_time = extract_times(stdout)
            if run_time is not None:
                run_times[size].append(run_time)
        except ValueError:
            continue
        run_times[size].append(run_time)
    print(f"Average runtime: {sum(run_times[size]) / args.count}")

    with open(f"data/raw1_{args.write_buffer}_{args.read_buffer}.json", "w") as fp:
        json.dump(run_times, fp)
