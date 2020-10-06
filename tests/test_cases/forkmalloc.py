#!/bin/python2
# Checks if forkmalloc.c runs the same natively as it does within Lind
import sys

lind_result = sys.argv[1].split('\n')
host_result = sys.argv[2].split('\n')

if len(lind_result) != len(host_result):
    print "Mismatched number of lines"
    exit(-1)

if (lind_result[0] != host_result[0]) or \
    (lind_result[2] != host_result[2]):
    print "Mismatched deterministic lines?!"
    exit(-1)

lind = lind_result[1].split(' ')
try:
    temp = int(lind[-1], 16)
except ValueError:
    print "Nondeterministic part of unrecognized format"
    exit(-1)