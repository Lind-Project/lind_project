#!/bin/python2
# Checks if pipeonestring.c runs the same natively as it does within Lind
# For each line, the result is stripped from trailing numbers and compared with each other.
import sys
import string

lind_result = sys.argv[1].split('\n')
host_result = sys.argv[2].split('\n')

if len(lind_result) != len(host_result):
    print "Mismatched number of lines!"
    exit(-1)

resultLen = len(lind_result)
print resultLen
for line in range(0,resultLen):
    if lind_result[line].rstrip(string.digits) != host_result[line].rstrip(string.digits):
        print "Nondeterministic lines of an unrecognized format!"
        exit(-1)
