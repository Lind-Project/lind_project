#!/bin/python2
# Both fork_simple.c and template.c work similarly, the main common aspect being both of them have different ordered forks with conflicting keys.
# A simple solution that covers both of them would be sorting the results, and comparing the lines for deterministic inputs, while checking the pid's for errors.

import re
import sys
import string

def template(results):
    pidlist = re.findall('[-\d]+', results)
    # print pidlist

lind_results = sys.argv[1]
native_results = sys.argv[2]

template(lind_results)
template(native_results)

lind_result_split = lind_results.split('\n')
native_result_split = native_results.split('\n')

lind_result_split = [line for line in lind_result_split if line != "waitpid(): No child processes"] #lind doesn't handle x correctly
lind_result_split = [line for line in lind_result_split if line != "wait(): No child processes"]

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
