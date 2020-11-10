#!/bin/python2
# Checks if pipe.c runs the same natively as it does within Lind
import sys

lind_result = sys.argv[1].split('\n')
host_result = sys.argv[2].split('\n')

lind_line0 = lind_result[0].split(',')
host_line0 = host_result[0].split(',')

if not (lind_line0[0][-1].isdigit() and lind_line0[1][1].isdigit() \
    and host_line0[0][-1].isdigit() and host_line0[1][1].isdigit()):
    print "Nondeterministic lines of an unrecognized format!"
    exit(-1)