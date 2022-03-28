#Base files:
cp /etc/hosts /home/lind/lind_project/hosts
echo -e "127.0.0.1\tLind" >> /home/lind/lind_project/hosts
lindfs cp /home/lind/lind_project/hosts /etc/hosts # Adjusted as we also need Lind's ip as 127.0.0.1 in the list.
rm /home/lind/lind_project/hosts
lindfs cp /etc/resolv.conf /etc/resolv.conf
lindfs cp /etc/nsswitch.conf /etc/nsswitch.conf
lindfs cp /etc/host.conf /etc/host.conf
lindfs cp /usr/share/zoneinfo/America/New_York /etc/localtime # As we don't have /etc/localtime default in lind.

#Coreutils
cd /home/lind/lind_project/tests/applications/coreutils/src;
find . -perm /a+x -type f -exec lindfs cp /home/lind/lind_project/tests/applications/coreutils/src/{} /bin/{} \;

#Bash
lindfs cp /home/lind/lind_project/tests/applications/bash/bash /bin/bash
lindfs cp /home/lind/lind_project/tests/applications/bash/bash /bin/sh

#Python
lindfs cp /home/lind/lind_project/tests/applications/python/python /bin/python;
lindfs cp /home/lind/lind_project/tests/applications/python/libpython2.7.so.1.0 /lib/glibc/libpython2.7.so.1.0
lindfs cp /home/lind/lind_project/tests/applications/python/Lib /usr/local/lib/python2.7
lindfs cp /home/lind/lind_project/tests/applications/python/Makefile /usr/lib/python2.7/config/Makefile
lindfs cp /home/lind/lind_project/tests/applications/python/pyconfig.h /usr/include/python2.7/pyconfig.h
lindfs cp /home/lind/lind_project/src/scripts/includes/passwd /etc/passwd

#Python Libs
echo Copying files...
libsarray=('_collections' 'operator' 'itertools' '_struct' 'math' 'binascii' 'time' 'cStringIO' '_random' 'array' '_socket' '_functools' 'cPickle' '_struct' 'select' 'array' 'unicodedata' 'fcntl')
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

#Flask
lindfs cp /home/lind/lind_project/tests/applications/python-modules/flask/ /usr/local/lib/python2.7/

#Openssl
lindfs cp /home/lind/lind_project/tests/applications/openssl/libcrypto.so.1.0.0 /lib/glibc/libcrypto.so.1.0.0
lindfs cp /home/lind/lind_project/tests/applications/openssl/libssl.so.1.0.0 /lib/glibc/libssl.so.1.0.0

#Postgres
lindfs cp /home/lind/lind_project/tests/applications/postgres/src/interfaces/libpq/libpq.so.5.13 /lib/glibc/libpq.so.5

#Psycopg2
lindfs cp /home/lind/lind_project/tests/applications/python-modules/psycopg2/lib/ /usr/local/lib/python2.7/lib-dynload/psycopg2/
