#!/bin/python2
import sys

lind_result = sys.argv[1].split('\n')
host_result = sys.argv[2].split('\n')

if len(lind_result) != len(host_result):
    print "mismatched number of lines"
    exit(-1)

if lind_result[1] != host_result[1]:
    print "mismatched deterministic lines"
    exit(-1)

if lind_result[0] != host_result[0]:
    print "mismatched messages written to STDOUT_FILENO"
    exit(-1)