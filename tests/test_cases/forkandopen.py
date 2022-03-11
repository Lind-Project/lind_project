#!/bin/python2
# Checks if forkandopen.c runs the same natively as it does within Lind
import re
import sys
import string

# assert(int(fdlist[-4]) != -1) checks if the parent PID's return -1. This would be an error with parent processes, but not with child processes.
def forkandopen(results):
    pidlist = re.findall('[-\d]+', results)
    print pidlist
    assert(int(pidlist[-4]) != -1)  # Checks if parent PID is not -1, which means failure.

lind_results = sys.argv[1]
native_results = sys.argv[2]

forkandopen(lind_results)
forkandopen(native_results)

lind_result_split = lind_results.split('\n')
native_result_split = native_results.split('\n')

lind_result_sort = lind_result_split.sort()
native_result_sort = native_result_split.sort()

# Deterministic line comparisons
if len(lind_result_sort) != len(native_result_sort):
    print "Mismatched number of lines!"
    exit(-1)

resultLen = len(lind_result_sort)
for line in range(0,resultLen):
    if lind_result_sort[line].translate(None, string.digits+'-') != native_result_sort[line].translate(None, string.digits+'-'):
        print "Nondeterministic lines of an unrecognized format!"
        exit(-1)