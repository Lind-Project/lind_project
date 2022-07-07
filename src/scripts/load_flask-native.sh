#!/bin/bash
#Builds Flask in native.
export LD_LIBRARY_PATH="/home/lind/lind_project/lind/lindenv/:/lib/glibc:"
echo "Compiling markupsafe/_speedups.so..."
cd /home/lind/lind_project/tests/applications/python-modules/flask/site-packages/markupsafe
gcc -DPY_FORMAT_LONG_LONG=ll -std=c99 -fPIC -fno-strict-aliasing -march=x86-64 -mtune=generic -O2 -pipe -DNDEBUG -I. -I/home/lind/lind_project/tests/applications/python/python-native/Include/ -I/home/lind/lind_project/tests/applications/python/python-native -c _speedups.c -o _speedups.o
gcc _speedups.o -o _speedups.so -pthread -shared -Wl,-O1 -Wl,-Bsymbolic-functions -std=c99 -L. -L/home/lind/lind_project/tests/applications/python/python-native -lpython2.7
rm _speedups.o

echo "Copying flask files:"
cp -r /home/lind/lind_project/tests/applications/python-modules/flask/site-packages/* /home/lind/lind_project/fake_fs/usr/local/lib/python2.7/site-packages/
