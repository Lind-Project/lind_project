#!/bin/bash
# Builds and loads python executable into lind.

echo "Building python"
cd /home/lind/lind_project/tests/applications/python/;
./bootstrap_nacl;
lindfs cp /home/lind/lind_project/tests/applications/python/python /bin/python;

echo "Copying libraries and configs"
lindfs cp /home/lind/lind_project/tests/applications/python/libpython2.7.so.1.0 /lib/glibc/libpython2.7.so.1.0
lindfs cp /home/lind/lind_project/tests/applications/python/Lib /usr/local/lib/python2.7
lindfs cp /home/lind/lind_project/tests/applications/python/Makefile /usr/lib/python2.7/config/Makefile
lindfs cp /home/lind/lind_project/tests/applications/python/pyconfig.h /usr/include/python2.7/pyconfig.h
lindfs cp /home/lind/lind_project/src/scripts/includes/passwd /etc/passwd

echo "Python installed!"
