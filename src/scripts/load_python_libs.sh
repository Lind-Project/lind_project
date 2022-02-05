# Loads only the core modules.

./load_openssl.sh
cd /home/lind/lind_project/tests/applications/python
./fastcompile.sh

# Copies 
echo Copying files...
libsarray=('_collections' 'operator' 'itertools' '_struct' 'math' 'binascii' 'time' 'cStringIO' '_random' 'array' '_socket' '_functools' 'cPickle' '_struct' 'select' 'array' 'unicodedata')
length=${#libsarray[@]}
for (( i = 0; i < length; i++ ));
do
    lindfs cp /home/lind/lind_project/tests/applications/python/build/lib/${libsarray[i]}.so /usr/local/lib/python2.7/lib-dynload/${libsarray[i]}.so
done

lindfs cp /home/lind/lind_project/tests/applications/python/build/lib/datetime.so /usr/local/lib/python2.7/lib-dynload/datetime.so
lindfs cp /home/lind/lind_project/tests/applications/python/build/lib/_io.so /usr/local/lib/python2.7/lib-dynload/_io.so
lindfs cp /home/lind/lind_project/tests/applications/python/build/lib/zlib.so /usr/local/lib/python2.7/lib-dynload/zlib.so
lindfs cp /home/lind/lind_project/tests/applications/python/Modules/zlib/libz.so.1.2.3 /lib/glibc/libz.so.1
lindfs cp /home/lind/lind_project/tests/applications/python/build/lib/_ssl.so /usr/local/lib/python2.7/lib-dynload/_ssl.so
lindfs cp /home/lind/lind_project/tests/applications/python/build/lib/_hashlib.so /usr/local/lib/python2.7/lib-dynload/_hashlib.so
