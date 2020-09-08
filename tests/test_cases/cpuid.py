#!/bin/python2
import sys

lind_result = sys.argv[1]
host_result = sys.argv[2]

if lind_result != host_result:
    print "Mismatched cpuid"
    exit(-1)