#!/bin/python2
import sys

lind_result = sys.argv[1].split('\n')
host_result = sys.argv[2].split('\n')

if len(lind_result) != len(host_result):
    print "Mismatched number of lines"
    exit(-1)

if lind_result[0] != host_result[1]:
    print "Mismatched deterministic lines"
    exit(-1)"

if lind_result[1] != host_result[1]:
    print "Mismatched messages printed before the file contents"
    exit(-1)

if lind_result[2] != host_result[2]:
    print "Mismatched contents written in the file"
    exit(-1)