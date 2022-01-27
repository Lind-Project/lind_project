#!/bin/python2
# Checks if gethostname.c runs the same natively as it does within Lind
# Lind's hostname is compared with "Lind" value, and native hostname is compared with socket.gethostname.
import re
import sys
import string
import socket

lind_results = sys.argv[1]
native_results = sys.argv[2]

# Deterministic line comparisons
if (socket.gethostname() != native_results.split()[1]):
    print "Hostname does not match in native!"
    exit(-1)

if (lind_results.split()[1]!="Lind"):
    print "Hostname does not match in Lind."
    exit(-1)