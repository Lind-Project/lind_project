#!/bin/python2
# Checks if any failure occurs
import sys

lind_result = sys.argv[1]
host_result = sys.argv[2]

if "fail" in lind_result or "fail" in host_result:
    print "Certain failure occured"
    exit(-1)
