import argparse
import json
import re
from subprocess import Popen, PIPE, STDOUT

def extract_times(output):
    # Extract numbers from the 'write-start' and 'read-end' lines
    write_start_match = re.search(r'Starts sending: (\d+)', output)
    read_end_match = re.search(r'Ends receiving: (\d+)', output)
    if write_start_match and read_end_match:
        write_start = int(write_start_match.group(1))
        read_end = int(read_end_match.group(1))
        return (read_end - write_start) / 1000000
    else:
        return None

parser = argparse.ArgumentParser(
    description="Script to benchmark sending n GBs unix domain socket implementation with varying buffersize"
)
parser.add_argument(
    "-b",
    "--buffer",
    dest="buffer",
    type=str,
    default="x",
    help="Read buffer size",
)
parser.add_argument(
    "-c", 
    "--count", 
    dest="count", 
    type=int, 
    default=10, 
    help="Number of runs",
)
parser.add_argument(
    "-p",
    "--execution-command",
    dest="execution",
    type=str,
    required=True,
    help="Platform specific execution command",
)
args = parser.parse_args()

run_times = {}

for size in range(4, 17, 2):
    buffer_size = str(size) if args.buffer == "x" else args.buffer

    # Split the command string into a list
    command = args.execution.split()
    # Append the write buffer size as the last argument
    command.append(buffer_size)

    run_times[size] = []
    print(f"Buffer: {buffer_size}")
    
    for _ in range(args.count):
        output = Popen(
            command,
            stdout=PIPE,
            stderr=STDOUT,
        )
        stdout, _ = output.communicate()
        stdout = stdout.decode('utf-8')
        print(f"command: {command}")
        try:
            run_time = extract_times(stdout)
            if run_time is not None:
                run_times[size].append(run_time)
        except ValueError:
            continue
    print(f"Average runtime: {sum(run_times[size]) / args.count}")

    if args.execution == "lind /uds":
        platform = "lind"
        type = "uds"
    elif args.execution == "scripts/uds":
        platform = "nat"
        type = "uds"
    elif args.execution == "lind /pipe":
        platform = "lind"
        type = "pipe"
    else:
        platform = "nat"
        type = "pipe"
    with open(f"data/{type}_{platform}_{args.buffer}.json", "w") as fp:
        json.dump(run_times, fp)
        