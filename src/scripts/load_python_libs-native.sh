# Loads only the core modules.
export LD_LIBRARY_PATH="/home/lind/lind_project/lind/lindenv/:/lib/glibc:"

echo "Compiling Openssl"
cd /home/lind/lind_project/tests/applications/openssl
./Configure linux-x86_64 no-hw no-asm no-krb5 --prefix=build/ --openssldir=build/ssl -fPIC -shared -D_GNU_SOURCE
make CC=gcc

echo "Copying Openssl"
cp /home/lind/lind_project/tests/applications/openssl/libcrypto.so.1.0.0 /home/lind/lind_project/fake_fs/lib/libcrypto.so.1.0.0
cp /home/lind/lind_project/tests/applications/openssl/libssl.so.1.0.0 /home/lind/lind_project/fake_fs/lib/libssl.so.1.0.0

echo "Fast Compile"
cd /home/lind/lind_project/tests/applications/python/python-native
./fastcompile-native.sh

# Copies 
echo Copying files...
libsarray=('_collections' 'operator' 'itertools' '_struct' 'math' 'binascii' 'time' 'cStringIO' '_random' 'array' '_socket' '_functools' 'cPickle' '_struct' 'select' 'array' 'unicodedata' 'fcntl')
for lib in "${libsarray[@]}"
do
    cp /home/lind/lind_project/tests/applications/python/python-native/build/lib/$lib.so /home/lind/lind_project/fake_fs/usr/local/lib/python2.7/lib-dynload/$lib.so
done

cp /home/lind/lind_project/tests/applications/python/python-native/build/lib/datetime.so /home/lind/lind_project/fake_fs/usr/local/lib/python2.7/lib-dynload/datetime.so
cp /home/lind/lind_project/tests/applications/python/python-native/build/lib/_io.so /home/lind/lind_project/fake_fs/usr/local/lib/python2.7/lib-dynload/_io.so
cp /home/lind/lind_project/tests/applications/python/python-native/build/lib/zlib.so /home/lind/lind_project/fake_fs/usr/local/lib/python2.7/lib-dynload/zlib.so
cp /home/lind/lind_project/tests/applications/python/python-native/Modules/zlib/libz.so.1.2.3 /home/lind/lind_project/fake_fs/lib/libz.so.1
cp /home/lind/lind_project/tests/applications/python/python-native/build/lib/_ssl.so /home/lind/lind_project/fake_fs/usr/local/lib/python2.7/lib-dynload/_ssl.so
cp /home/lind/lind_project/tests/applications/python/python-native/build/lib/_hashlib.so /home/lind/lind_project/fake_fs/usr/local/lib/python2.7/lib-dynload/_hashlib.so
