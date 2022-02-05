#!/bin/bash
# Builds and loads python executable into lind.

echo "Building python"
cd /home/lind/lind_project/tests/applications/python/;
./bootstrap_nacl;
lindfs cp /home/lind/lind_project/tests/applications/python/python /bin/python;

echo "Copying libraries and configs"
lindfs cp /home/lind/lind_project/tests/applications/python/libpython2.7.so.1.0 /lib/glibc/libpython2.7.so.1.0
lindfs cp /home/lind/lind_project/tests/applications/python/Lib /usr/local/lib/python2.7
lindfs cp /usr/lib/python2.7/config/ /usr/lib/python2.7/config/
lindfs cp /usr/include/python2.7/ /usr/include/python2.7/
lindfs cp /home/lind/lind_project/src/scripts/includes/passwd /etc/passwd

echo "Python installed!"
