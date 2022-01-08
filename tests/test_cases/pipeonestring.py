#!/bin/python2
# Checks if pipeonestring.c runs the same natively as it does within Lind
# For each line, the result is stripped from trailing numbers and compared with each other.
import sys
import string

lind_result = sys.argv[1].split('\n')
host_result = sys.argv[2].split('\n')

# Deterministic line comparison
if len(lind_result) != len(host_result):
    print "Mismatched number of lines!"
    exit(-1)

resultLen = len(lind_result)
for line in range(0,resultLen):
    if lind_result[line].rstrip(string.digits) != host_result[line].rstrip(string.digits):
        print "Lines do not match!"
        exit(-1)

# Nondeterministic digit check
lind_parent = lind_result[1].split(' ')[-1]
lind_child = lind_result[2].split(' ')[-1]
host_parent = host_result[1].split(' ')[-1]
host_child = host_result[2].split(' ')[-1]
if (lind_parent.isdigit() or lind_child.isdigit()):
    print "Nondeterministic lines of unrecognized format in lind output."
    exit(-1)
if (host_parent.isdigit() or host_child.isdigit()):
    print "Nondeterministic lines of unrecognized format in regular output."
    exit(-1)
