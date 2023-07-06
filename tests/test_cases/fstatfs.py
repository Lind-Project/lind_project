#!/bin/python2
# Check if fstatfs.c runs correctly in native as it does within Lind
import sys
import re

# Receive result
lind_result = sys.argv[1]
host_result = sys.argv[2]

# Extract output
# sample output: Filesystem type: beefcOde
match = re.search(r'Filesystem type: (\w+)', lind_result)
if match:
    lind_string = match.group(1)
# Expect lind output: beefcOde
if lind_string != "beefc0de":
    print "Lind info: ", lind_string
    exit(-1)

# Extract output
# sample output: Filesystem type: 794c7630
match2 = re.search(r'Filesystem type: (\w+)', host_result)
if match2:
    host_string = match2.group(1)
# Expect host output: 794c7630
if host_string != "794c7630":
    print "Host info: ", host_string
    exit(-1)
