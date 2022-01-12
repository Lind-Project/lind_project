#!/bin/python2
# Checks if segfault.c runs the same natively as it does within Lind

import sys
import string

lind_result = sys.argv[1].split('\n')
host_result = sys.argv[2].split('\n')

# Deterministic line comparison
if len(lind_result) != len(host_result):
    print "Mismatched number of lines!"
    exit(-1)

# Both isdigit and comparisons are done in one check.
resultLen = len(lind_result)
for line in range(0,resultLen):
    if lind_result[line].rstrip(string.digits + '[, ]') != host_result[line].rstrip(string.digits + '[, ]'):
        print "Lines do not match!"
        exit(-1)