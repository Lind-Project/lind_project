#!/bin/python2
# Checks if serverclient.c runs the same natively as it does within Lind
# The result is sorted to avoid different ordered outputs, and compared with each other.
import re
import sys
import string

lind_results = sys.argv[1]
native_results = sys.argv[2]

lind_result_split = lind_results.split('\n')
native_result_split = native_results.split('\n')

lind_result_sort = lind_result_split.sort()
native_result_sort = native_result_split.sort()

# Deterministic line comparisons
if len(lind_result_split) != len(lind_result_split):
    print "Mismatched number of lines!"
    exit(-1)

resultLen = len(lind_result_split)
for line in range(0,resultLen):
    if lind_result_split[line].translate(None, string.digits+'-') != native_result_split[line].translate(None, string.digits+'-'):
        print "Nondeterministic lines of an unrecognized format!"
        exit(-1)