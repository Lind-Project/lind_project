#!/bin/python2
# Checks if pipescript runs the same natively as it does within Lind
import sys

lind_result = sys.argv[1].split('\n')
host_result = sys.argv[2].split('\n')

if len(lind_result) != len(host_result):
    print "Mismatched number of lines"
    exit(-1)

host_freq = {}
for line in host_result:
    last_char_buffer = line[-1]
    host_freq[last_char_buffer] = host_freq.get(last_char_buffer, 0) + 1

lind_freq = {}
for line in lind_result:
    last_char_buffer = line[-1]
    lind_freq[last_char_buffer] = lind_freq.get(last_char_buffer, 0) + 1

if host_freq != lind_freq:
    print "Mismatched shared buffer contents"
    exit(-1)
