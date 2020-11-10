#!/bin/python2
# Checks if pipe.c runs the same natively as it does within Lind
import sys

lind_result = sys.argv[1].split('\n')
host_result = sys.argv[2].split('\n')

lind_line0 = lind_result[0].spilt(',')
host_line0 = host_result[0].split(',')

if not (lind_line0[0][-1].isdigit() and lind_line0[1][1].isdigit() \
    and host_line0[0][-1].isdigit() and host_line[1][1].isdigit()):
    print "Nondeterministic lines of an unrecognized format!"
    exit(-1)

lind_line1 = lind_result[1].split(": ")[1]
host_line1 = host_result[1].split(": ")[1]

if not (lind_line1.isdigit() and host_line1.isdigit()):
    print "Nondeterministic lines of an unrecognized format!"
    exit(-1)

if lind_line1 != host_line1:
    print "Mismatched number of bytes written!"
    exit(-1)

lind_line2 = lind_result[2].split(": ")[1]
host_line2 = host_result[2].split(": ")[1]

if not (lind_line2.isdigit() and host_line2.isdigit()):
    print "Nondeterministic lines of an unrecognized format!"
    exit(-1)

if lind_line2 != host_line2:
    print "Mismatched number of bytes read!"
    exit(-1)