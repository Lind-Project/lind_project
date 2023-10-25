#!/bin/python2
# Check if uds-socketselect.c runs correctly in native as it does within Lind

import re
import sys

# Receive result
lind_results = sys.argv[1]
native_results = sys.argv[2]

# Extract output
lind_result_split = lind_results.split('\n')
native_result_split = native_results.split('\n')

# Check if the number of lines are the same
if len(lind_result_split) != len(native_result_split):
    print "Mismatched number of lines!"
    exit(-1)

# Check if the lines are the same
for i in range(len(lind_result_split)):
    if lind_result_split[i].find("New incoming connection") != -1 or lind_result_split[i].find("Descriptor") != -1:
        lind_result_split[i] = re.sub("\d", "*", lind_result_split[i])
    if native_result_split[i].find("New incoming connection") != -1 or native_result_split[i].find("Descriptor") != -1:
        native_result_split[i] = re.sub("\d", "*", native_result_split[i])
    if lind_result_split[i] != native_result_split[i]:
        print "Mismatched lines!\nLind: " + lind_result_split[i] + "\nNative: " + native_result_split[i]
        exit(-1)
