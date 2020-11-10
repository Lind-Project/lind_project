#!/bin/python2
# Checks if pipeinput.c runs the same natively as it does within Lind
import sys

lind_result = sys.argv[1].split('\n')
host_result = sys.argv[2].split('\n')

if not (lind_result[1].split(": ")[1].isdigit() \
    and host_result[1].split(": ")[1].isdigit()):
    print "Nondeterministic lines of an unrecognized format!"
    exit(-1)