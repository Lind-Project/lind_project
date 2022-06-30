#!/bin/bash
# Builds and loads python executable into lind.

mkdir -p /home/lind/lind_project/fake_fs
mkdir -p /home/lind/lind_project/fake_fs/bin
mkdir -p /home/lind/lind_project/fake_fs/lib
mkdir -p /home/lind/lind_project/fake_fs/usr/local/lib/
mkdir -p /home/lind/lind_project/fake_fs/usr/lib/python2.7/config
mkdir -p /home/lind/lind_project/fake_fs/usr/include/python2.7
mkdir -p /home/lind/lind_project/fake_fs/usr/local/lib/python2.7/lib-dynload/

echo "Building python"
cd /home/lind/lind_project/tests/applications/python/python-native;
./configure --enable-shared;
make;
cp /home/lind/lind_project/tests/applications/python/python-nativee/python /home/lind/lind_project/fake_fs/bin/python;

echo "Copying libraries and configs"
cp /home/lind/lind_project/tests/applications/python/python-native/libpython2.7.so.1.0 /home/lind/lind_project/fake_fs/lib/libpython2.7.so.1.0
rm -rf /home/lind/lind_project/tmp
cp -r /home/lind/lind_project/tests/applications/python/python-native/Lib/* /home/lind/lind_project/fake_fs/usr/local/lib/python2.7/
cp /home/lind/lind_project/tests/applications/python/python-native/Makefile /home/lind/lind_project/fake_fs/usr/lib/python2.7/config/Makefile
ecp /home/lind/lind_project/tests/applications/python/python-native/pyconfig.h /home/lind/lind_project/fake_fs/usr/include/python2.7/pyconfig.h

echo "Python installed!"
