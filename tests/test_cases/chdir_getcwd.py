#!/bin/python2
# Checks if chdir_getcwd.c runs the same natively as it does within Lind
# Since it changes the directory, we only need to compare the difference before and after to make sure it runs correctly natively and on lind.
import sys

lind_result = sys.argv[1].split('\n')
host_result = sys.argv[2].split('\n')

if len(lind_result) != len(host_result):
    print "Mismatched number of lines"
    exit(-1)

# Sample output: current working directory is: / :: /
# chdir is "test/".
lind_init_cwd = lind_result[0].split('::')[1] # Initial cwd
lind_res_cwd = lind_result[1].split('::')[1] # Result cwd
host_init_cwd = host_result[0].split('::')[1] # Initial cwd
host_res_cwd = host_result[1].split('::')[1] # Result cwd

# The difference between them should be equal to regularoutput's. 
if lind_res_cwd.replace(lind_init_cwd,"/") != host_res_cwd.replace(host_init_cwd,""):
    print "The cwd's do not match!"
    exit(-1)