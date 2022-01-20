#!/bin/python2
# Checks if fork2malloc.c runs the same natively as it does within Lind
import sys

lind_result = sys.argv[1].split('\n')
host_result = sys.argv[2].split('\n')

# Directly compare deterministic parts/lines.
if len(lind_result) != len(host_result):
    print "Mismatched number of lines"
    exit(-1)
# Nondeterministic checks are done by value checking for integer.
for i in range(len(lind_result)):
    curr_line = lind_result[i].split(' ')
    if curr_line[0] == "Address":
        host_line = host_result[i].split(' ')
        try:
            temp = int(curr_line[-1], 16)
        except ValueError:
            print "Nondeterministic part of unrecognized format"
            exit(-1)
        try:
            temp = int(host_line[-1], 16)
        except ValueError:
            print "Nondeterministic part of unrecognized format"
            exit(-1)
    elif curr_line[0] == "Contents":
        host_line = host_result[i].split(' ')
        if curr_line[-1] != host_line[-1]:
            print "Nondeterministic part of mismatched contents"
            exit(-1)
    else:
        if lind_result[i] != host_result[i]:
            print "Mismatched deterministic lines?!"
            exit(-1)