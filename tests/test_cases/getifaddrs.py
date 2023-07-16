#!/bin/python2
# Checks if getifaddrs.c runs the same natively as it does within Lind
# Since we expect each line to be of the format:
# <string> <AF_INET|AF_PACKET|AF_INET6> (number)
# we can loop over each line of the lindoutput and hostoutput and
# verify that this is indeed the case
import sys
lindoutput = sys.argv[1].split('\n')
hostoutput = sys.argv[2].split('\n')

# List of possible family names (for the second token)
family_names = ["AF_INET", "AF_PACKET", "AF_INET6", "???"]

# Helper function to verify the output
def verify(output):
    tokens = output.split()

    if len(tokens) != 3:
        print "Expected only 3 tokens on each line:", len(tokens)
        exit(-1)

    if not (tokens[1] in family_names):
        print "Unexpected value for second token"
        exit(-1)

    if not (tokens[2][1:-1].isdigit() and tokens[2][0] == '(' and tokens[2][-1] == ')'):
        print "Expected the last token to be numeric"
        exit(-1)

for line in lindoutput:
    verify(line)

for line in hostoutput:
    verify(line)

