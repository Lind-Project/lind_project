#!/bin/python2
# Checks if fork.c runs the same natively as it does within Lind
import sys

lind_result = sys.argv[1].split('\n')
host_result = sys.argv[2].split('\n')

host = {}
for line in host_result:
    host[line[5:7]] = line[9:]

for line in lind_result:
    key = line[5:7]
    if key in host:
        host_line = host[key].split(' ')
        for i in range(len(host_line)):
            host_line[i] = host_line[i].replace(',', '')
        lind_line = line[9:].split(' ')
        for i in range(len(lind_line)):
            lind_line[i] = lind_line[i].replace(',', '')
        for i in range(len(host_line)):
            if host_line[i].isdigit():
                if not lind_line[i].isdigit():
                    print "Nondeterministic part of unrecognized format"
                    exit(-1)
            else:
                if host_line[i] != lind_line[i]:
                    print "Mismatched deterministic parts?!"
                    exit(-1)
        del host[key]
    elif key.isdigit():
        print "Extra lines in Lind output"
        exit(-1)

if len(host) != 0:
    print "Lines missing in Lind output"
    exit(-1)