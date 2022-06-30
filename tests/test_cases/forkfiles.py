#!/bin/python2
# Checks if forkfiles.c runs the same natively as it does within Lind
import sys

lind_result = sys.argv[1].split('\n')
host_result = sys.argv[2].split('\n')

# Compares lines.
if len(lind_result) != len(host_result):
    print "Mismatched number of lines"
    exit(-1)

if lind_result[0] != host_result[0]:
    print "Mismatched deterministic lines?!"
    exit(-1)

lind = lind_result[1].split(' ')
host = lind_result[1].split(' ')

# Compares read char numbers.
if not (lind[1].isdigit() and host[1].isdigit()):
    print "Nondeterministic part of unrecognized format"
    exit(-1)

if lind[1] != host[1]:
    print "Mismatched number of bytes read"
    exit(-1)