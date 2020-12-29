#!/bin/python2
# Checks if pipeonestring.c runs the same natively as it does within Lind
import sys

lind_result = sys.argv[1].split('\n')
host_result = sys.argv[2].split('\n')

if len(lind_result) != len(host_result):
    print "Mismatched number of lines!"
    exit(-1)

for line in lind_result:
    if line[0] == 'I' and (not line.split(": ")[1].isdigit()):
        print "Nondeterministic lines of an unrecognized format!"
        exit(-1)

for line in host_result:
    if line[0] == 'I' and (not line.split(": ")[1].isdigit()):
        print "Nondeterministic lines of an unrecognized format!"
        exit(-1)
        