#!/bin/python2
# Checks if pipeonestring.c runs the same natively as it does within Lind
# For each line, the result is stripped from trailing numbers and compared with each other.
import sys
import string

lind_result = sys.argv[1].split('\n')
native_result = sys.argv[2].split('\n')

lind_result.sort(reverse=True)
native_result.sort(reverse=True)

""" A default output looks like this:
Parent: Testing open in parent: pid 218238!
Parent: Pid 218238 opened fd 4
Child: Testing open in child: pid 0!
Child: Pid 0 opened fd -1 

But if we order them; it will make sure the order does match with lind as we don't promise the same order.

Alphabetically reverse ordering will give us the output in the same order. P...Test/P...Pid/C...Test/C...Pid

"""

# Deterministic line comparison
if len(lind_result) != len(native_result):
    print "Mismatched number of lines!"
    exit(-1)

resultLen = len(lind_result)
for line in range(0,resultLen):
    if lind_result[line].rstrip(string.digits) != native_result[line].rstrip(string.digits):
        print "Lines do not match!"
        exit(-1)

# Nondeterministic digit check
lind_parent = lind_result[1].split(' ')[-1]
lind_child = lind_result[2].split(' ')[-1]
native_parent = native_result[1].split(' ')[-1]
native_child = native_result[2].split(' ')[-1]

if not (lind_parent.isdigit() or lind_child.isdigit()):
    print "Nondeterministic lines of unrecognized format in lind output."
    exit(-1)
if not (native_parent.isdigit() or native_child.isdigit()):
    print "Nondeterministic lines of unrecognized format in regular output."
    exit(-1)
