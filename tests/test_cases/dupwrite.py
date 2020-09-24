#!/bin/python2
import sys

lind_result = sys.argv[1].split('\n')
host_result = sys.argv[2].split('\n')

if len(lind_result) != len(host_result):
    print "Mismatched number of lines"
    exit(-1)

if lind_result != host_result:
    print "Mismatched messages written to dup fd"
    exit(-1)