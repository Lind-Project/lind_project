#!/bin/python2
# Checks if dup.c runs the same natively as it does within Lind
import sys

lind_result = sys.argv[1].split('\n')
host_result = sys.argv[2].split('\n')

if len(lind_result) != len(host_result):
    print "Mismatched number of lines"
    exit(-1)

lind_result.remove('')
lind_result.remove('')
host_result.remove('')
host_result.remove('')

# Checks nondeterministic (pid) output validity by digit checking.
if not (lind_result[0][-1].isdigit() and host_result[0][-1].isdigit()):
    print "Nondeterministic lines of unrecognized format"
    exit(-1)

# Directly compare deterministic parts/lines.
if lind_result[1] != host_result[1]:
    print "Mismatched deterministic lines"
    exit(-1)

if lind_result[2] != host_result[2]:
    print "Mismatched content written to dup() fd"
    exit(-1)

if lind_result[3] != host_result[3]:
    print "Mismatched content written to old fd"
    exit(-1)