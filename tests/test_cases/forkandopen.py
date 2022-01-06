#!/bin/python2
# Checks if forkandopen.c runs the same natively as it does within Lind
import re
import sys

def forkandopen(results):
    pidlist = re.findall('[-\d]+', results)
    print pidlist
    assert(int(pidlist[-4]) != -1)  # Checks if parent PID is not -1, which means failure

lind_results = sys.argv[1]
native_results = sys.argv[2]

forkandopen(lind_results)
forkandopen(native_results)
