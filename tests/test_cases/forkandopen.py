#!/bin/python2
# Checks if forkandopen.c runs the same natively as it does within Lind
import re
import sys

def forkandopen(results):
    fdlist = re.findall('[-\d]+', results)
    assert(int(fdlist[-4]) != -1)

lind_results = sys.argv[1]
native_results = sys.argv[2]

forkandopen(lind_results)
forkandopen(native_results)
