import argparse
import json
import re
import os
from subprocess import Popen, PIPE
    
def run_test(count, command, platform, type):
    for _ in range(count):
        # Append instead of overwrite
        with open(f"outputs/{platform}_{type}.txt", "a") as output_file:
            _ = Popen(
                command,
                stdout=output_file,
                stderr=PIPE
            )

def tail_n_1(file_path, buf_size, platform):
    results = {}
    with open(file_path, 'rb') as f:
        # Seek from last line
        f.seek(-2, os.SEEK_END)
        while f.read(1) != b'\n':
            f.seek(-2, os.SEEK_CUR)
        last_line = f.readline().decode()
        results[buf_size] = re.search(r'average time (\d+)', last_line)
    
    # Write to json file
    with open(f'{platform}_write.json', 'w') as fp:
        json.dump(results, fp)

parser = argparse.ArgumentParser(
    description="SFI Penalty Tests"
)
parser.add_argument(
    "-c", 
    "--count", 
    dest="count", 
    type=int, 
    default=10, 
    help="Number of runs",
)
args = parser.parse_args()

run_times = {}

platforms = ['nat', 'lind']

for buf_size in range(1, 16, 256, 4096, 65536):
    print(f'Write tests ---- Native Linux')
    nat_write_command = ['scripts/write', buf_size]
    run_test(args.count, nat_write_command, 'nat', f'write_{buf_size}')

    print(f'Write tests ---- Lind')
    lind_write_command = ['lind', '/write.nexe', buf_size]
    run_test(args.count, lind_write_command, 'lind', f'write_{buf_size}')

    for platform in platforms:
        # Extract write() test results into json file
        tail_n_1(f'output/{platform}_write_{buf_size}.txt', buf_size, platform)

print(f'--------------------------------------------------------------------')
print(f'Close test ---- Native Linux')
run_test(args.count, 'scripts/close', 'nat', 'close')

print(f'Close test ---- Lind')
run_test(args.count, 'lind','/close.nexe', 'lind', 'close')

print(f'--------------------------------------------------------------------')
print(f'Getpid test ---- Native Linux')
run_test(args.count, 'scripts/getpid', 'nat', 'getpid')

print(f'Getpid test ---- Lind')
run_test(args.count, 'lind','/getpid.nexe', 'lind', 'getpid')


