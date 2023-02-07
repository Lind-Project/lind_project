#!/bin/python2
# Checks if any failure occurs
import sys

lind_result = sys.argv[1]
host_result = sys.argv[2]

# Extract numbers sent and received by ponger and pingers
lind_numbers = [int(line.split(':')[1]) for line in lind_result.split('\n') if ':' in line]
lind_numbers.sort()
host_numbers = [int(line.split(':')[1]) for line in host_result.split('\n') if ':' in line]
host_numbers.sort()

if lind_numbers != host_numbers:
    print "Numbers don't match"
    exit(-1)

if "fail" in lind_result or "fail" in host_result:
    print "Certain failure occured"
    exit(-1)
