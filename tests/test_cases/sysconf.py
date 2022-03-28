#!/bin/python2
# Checks if sysconf.c runs the same natively as it does within Lind
# As pagesizes are fixed, we can only compare them with their fixed values.
import sys
import string

lind_result = sys.argv[1].split('\n')
host_result = sys.argv[2].split('\n')

# Checking deterministic output
resultLen = len(lind_result)
for line in range(0,resultLen):
    if lind_result[line].rstrip(string.digits) != host_result[line].rstrip(string.digits):
        print "Lines do not match!"
        exit(-1)

# Ensuring pagefile output correctness
if lind_result[1].split(": ")[1] != "65536" and host_result[1].split(": ")[1] != "4096":
    print "Pagefiles do not match!"
    exit(-1)