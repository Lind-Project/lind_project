#!/bin/bash

sudo mkdir -p /usr/local/python-gcc4/{bin,lib,include,lib-dynload,site-packages}

echo "Copying libraries and configs"
sudo cp /home/lind/lind_project/tests/applications/python-native-gcc4/python-gcc4/python /usr/local/python-gcc4/bin/python;

sudo cp /home/lind/lind_project/tests/applications/python-native-gcc4/python-gcc4/libpython2.7.so.1.0 /usr/local/python-gcc4/lib/
sudo cp -r /home/lind/lind_project/tests/applications/python-native-gcc4/python-gcc4/Lib /usr/local/python-gcc4/lib/
sudo cp -r /home/lind/lind_project/tests/applications/python/Lib /usr/local/python-gcc4/lib
# lindfs cp /home/lind/lind_project/tests/applications/python/Makefile /usr/local/lib/python2.7/config/Makefile
sudo cp /home/lind/lind_project/tests/applications/python-native-gcc4/python-gcc4/pyconfig.h /usr/local/python-gcc4/pyconfig.h
# lindfs cp /home/lind/lind_project/src/scripts/includes/passwd /etc/passwd

echo "Python installed!"
echo "Copying Openssl"
sudo cp /home/lind/lind_project/tests/applications/python-native-gcc4/openssl/libcrypto.so.1.0.0 /lib/libcrypto.so.1.0.0
sudo cp /home/lind/lind_project/tests/applications/python-native-gcc4/openssl/libssl.so.1.0.0 /lib/libssl.so.1.0.0

# Copies 
echo Copying files...
libsarray=('_collections' 'operator' 'itertools' '_struct' 'math' 'binascii' 'time' 'cStringIO' '_random' 'array' '_socket' '_functools' 'cPickle' '_struct' 'select' 'array' 'unicodedata' 'fcntl' 'grp')
for lib in "${libsarray[@]}"
do
    sudo cp /home/lind/lind_project/tests/applications/python-native-gcc4/python-gcc4/build/lib/$lib.so /usr/local/python-gcc4/lib-dynload/$lib.so
done

sudo cp /home/lind/lind_project/tests/applications/python-native-gcc4/python-gcc4/build/lib/datetime.so /usr/local/python-gcc4/lib-dynload/datetime.so
sudo cp /home/lind/lind_project/tests/applications/python-native-gcc4/python-gcc4/build/lib/_io.so /usr/local/python-gcc4/lib-dynload/_io.so
sudo cp /home/lind/lind_project/tests/applications/python-native-gcc4/python-gcc4/build/lib/zlib.so /usr/local/python-gcc4/lib-dynload/zlib.so
sudo cp /home/lind/lind_project/tests/applications/python-native-gcc4/python-gcc4/Modules/zlib/libz.so.1.2.3 /usr/local/python-gcc4/libz.so.1
sudo cp /home/lind/lind_project/tests/applications/python-native-gcc4/python-gcc4/build/lib/_ssl.so /usr/local/python-gcc4/lib-dynload/_ssl.so
sudo cp /home/lind/lind_project/tests/applications/python-native-gcc4/python-gcc4/build/lib/_hashlib.so /usr/local/python-gcc4/lib-dynload/_hashlib.so
sudo cp /home/lind/lind_project/tests/applications/python-native-gcc4/python-gcc4/build/lib/_ctypes.so /usr/local/python-gcc4/lib-dynload/_ctypes.so
sudo cp /home/lind/lind_project/tests/applications/python-native-gcc4/python-gcc4/build/lib/libffi.so /usr/local/python-gcc4/lib/libffi.so
sudo cp /home/lind/lind_project/tests/applications/python-native-gcc4/python-gcc4/build/lib/libffi.so /usr/local/python-gcc4/lib/libffi.so.5

echo "Copying flask files:"
sudo cp /home/lind/lind_project/tests/applications/python-native-gcc4/python-modules/site-packages/markupsafe/_speedups.so /usr/local/python-gcc4/site-packages/_speedups.so
sudo cp -r /home/lind/lind_project/tests/applications/python-native-gcc4/python-modules/site-packages/ /usr/local/python-gcc4/
