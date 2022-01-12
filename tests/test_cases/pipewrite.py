#!/bin/python2
# Checks if pipewrite.c runs the same natively as it does within Lind
import sys

lind_result = sys.argv[1].split('\n')
host_result = sys.argv[2].split('\n')

# Deterministic line comparison
if len(lind_result) != len(host_result):
    print "Mismatched number of lines!"
    exit(-1)

resultLen = len(lind_result)
for line in range(1,resultLen):
    if lind_result[line] != host_result[line]:
        print "Lines do not match!"
        exit(-1)

# Nondeterministic digit check
lind_line0 = lind_result[0].split("end ")
host_line0 = host_result[0].split("end ")

if not(lind_line0[1][0].isdigit() and lind_line0[2][0].isdigit() \
    and host_line0[1][0].isdigit() and host_line0[2][0].isdigit()):
    print "Nondeterministic lines of an unrecognized format!"
    exit(-1)