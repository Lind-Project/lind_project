#!/bin/bash
# loads python executable into lind.

echo "Copying libraries and configs"
lindfs cp /home/lind/lind_project/tests/applications/python/python /bin/python;

lindfs cp /home/lind/lind_project/tests/applications/python/libpython2.7.so.1.0 /lib/glibc/libpython2.7.so.1.0
lindfs cp /home/lind/lind_project/tests/applications/python/Lib /usr/local/lib/python2.7
lindfs cp /home/lind/lind_project/tests/applications/python/Makefile /usr/local/lib/python2.7/config/Makefile
lindfs cp /home/lind/lind_project/tests/applications/python/pyconfig.h /usr/local/include/python2.7/pyconfig.h
lindfs cp /home/lind/lind_project/src/scripts/includes/passwd /etc/passwd

echo "Python installed!"
echo "Copying Openssl"
lindfs cp /home/lind/lind_project/tests/applications/openssl/libcrypto.so.1.0.0 /lib/glibc/libcrypto.so.1.0.0
lindfs cp /home/lind/lind_project/tests/applications/openssl/libssl.so.1.0.0 /lib/glibc/libssl.so.1.0.0

# Copies 
echo Copying files...
libsarray=('_collections' 'operator' 'itertools' '_struct' 'math' 'binascii' 'time' 'cStringIO' '_random' 'array' '_socket' '_functools' 'cPickle' '_struct' 'select' 'array' 'unicodedata' 'fcntl' 'grp')
for lib in "${libsarray[@]}"
do
    lindfs cp /home/lind/lind_project/tests/applications/python/build/lib/$lib.so /usr/local/lib/python2.7/lib-dynload/$lib.so
done

lindfs cp /home/lind/lind_project/tests/applications/python/build/lib/datetime.so /usr/local/lib/python2.7/lib-dynload/datetime.so
lindfs cp /home/lind/lind_project/tests/applications/python/build/lib/_io.so /usr/local/lib/python2.7/lib-dynload/_io.so
lindfs cp /home/lind/lind_project/tests/applications/python/build/lib/zlib.so /usr/local/lib/python2.7/lib-dynload/zlib.so
lindfs cp /home/lind/lind_project/tests/applications/python/Modules/zlib/libz.so.1.2.3 /lib/glibc/libz.so.1
lindfs cp /home/lind/lind_project/tests/applications/python/build/lib/_ssl.so /usr/local/lib/python2.7/lib-dynload/_ssl.so
lindfs cp /home/lind/lind_project/tests/applications/python/build/lib/_hashlib.so /usr/local/lib/python2.7/lib-dynload/_hashlib.so
lindfs cp /home/lind/lind_project/tests/applications/python/build/lib/_ctypes.so /usr/local/lib/python2.7/lib-dynload/_ctypes.so
lindfs cp /home/lind/lind_project/tests/applications/python/build/lib/libffi.so /lib/glibc/libffi.so

echo "Copying flask files:"
lindfs cp /home/lind/lind_project/tests/applications/python-modules/site-packages/ /usr/local/lib/python2.7/site-packages/
