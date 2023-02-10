#!/bin/python2
# Checks if any failure occurs
import sys

lind_result = sys.argv[1]
host_result = sys.argv[2]

if lind_result.replace('.', '0').isdigit() and host_result.replace('.', '0').isdigit() and float(lind_result) < 1:
    exit(0)
else:
    print "Test case failed"
    exit(1)
