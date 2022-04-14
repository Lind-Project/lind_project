#!/bin/python2
# Checks if socketselect.c runs the same natively as it does within Lind
import sys
import string

lind_results = sys.argv[1]
native_results = sys.argv[2]

lind_result_split = lind_results.split('\n')
native_result_split = native_results.split('\n')

lind_result_split.sort(reverse=True)
native_result_split.sort(reverse=True)

# Deterministic line comparisons
if len(lind_result_split) != len(native_result_split):
    print "Mismatched number of lines!\n"
    print "Potential issue for select: If the test is run in quick successions, there's a possibility that the select has not been closed."
    exit(-1)

resultLen = len(lind_result_split)
for line in range(0,resultLen):
    if lind_result_split[line].translate(None, string.digits+'-') != native_result_split[line].translate(None, string.digits+'-'):
        print "Nondeterministic lines of an unrecognized format!"
        exit(-1)

# Hello received check, in sorted array, 5th line is "Hello from client".
if lind_result_split[4] != native_result_split[4]: 
    print "Hello mesage not received by lind!"
    exit(-1)
