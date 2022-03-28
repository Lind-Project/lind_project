#!/bin/python2
# Checks if read.c runs the same natively as it does within Lind
import sys
lindoutput = sys.argv[1].split('\n')
hostoutput = sys.argv[2].split('\n')

over = False
# Compares ret and left values for Lind.
for line in lindoutput:
    if line.startswith('read()'):
        first = line.find('[')
        fend = line.find(']')
        read = int(line[first + 1:fend])
        remaining = line[fend + 1:]
        first = remaining.find('[')
        fend = remaining.find(']')
        left = int(remaining[first + 1:fend])
        if read == left:
            over = True

if not over:
    print "Never read all of the necessary output"
    exit(-1)
