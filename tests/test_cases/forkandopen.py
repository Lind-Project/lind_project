#!/bin/python

#!/bin/python

import re
import sys

def forkandopen(results):
    fdlist = re.findall('[-\d]+', results)
    print fdlist
    assert(int(fdlist[-1]) != -1)
    assert(int(fdlist[-4]) != -1)


lind_results = sys.argv[1]
native_results = sys.argv[2]

print "Running forkandopen test"
forkandopen(lind_results)
forkandopen(native_results)

