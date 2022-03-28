#!/bin/python2
# Checks if getpid.c runs the same natively as it does within Lind
import sys
lindoutput = sys.argv[1].split('\n')
hostoutput = sys.argv[2].split('\n')

# Directly compare deterministic parts/lines.
lindoutput.remove('Success') #lind doesn't handle stderr correctly
if len(lindoutput) != len(hostoutput):
    print "Lind output and host output differ in number of lines"
    exit(-1)

for index, (lindline, hostline) in enumerate(zip(lindoutput, hostoutput)):
    if index != 1:
        if lindline != hostline:
            print "Deterministic lines mismatched?!"
            exit(-1)   
    else:
        # Checks nondeterministic (pid) output validtiy by digit checking.
        if not (lindline.isdigit() and hostline.isdigit()):
            print "Nondeterministic lines of unrecognized format"
            exit(-1)
