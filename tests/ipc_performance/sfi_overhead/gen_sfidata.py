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

for buf_size in [1, 16, 256, 4096, 65536]:
    print(f'Write tests ---- Native Linux')
    nat_write_command = ['scripts/write', str(buf_size)]
    run_test(args.count, nat_write_command, 'nat', f'write_{buf_size}')

    print(f'Write tests ---- Lind')
    lind_write_command = ['lind', '/write.nexe', str(buf_size)]
    run_test(args.count, lind_write_command, 'lind', f'write_{buf_size}')

print(f'--------------------------------------------------------------------')
print(f'Close test ---- Native Linux')
run_test(args.count, 'scripts/close', 'nat', 'close')

print(f'Close test ---- Lind')
lind_close_command = ['lind','/close.nexe']
run_test(args.count, lind_close_command, 'lind', 'close')

print(f'--------------------------------------------------------------------')
print(f'Getpid test ---- Native Linux')
run_test(args.count, 'scripts/getpid', 'nat', 'getpid')

print(f'Getpid test ---- Lind')
lind_getpid = ['lind','/getpid.nexe']
run_test(args.count, lind_getpid, 'lind', 'getpid')


