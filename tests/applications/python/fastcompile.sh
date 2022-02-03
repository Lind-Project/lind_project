echo "Starting...";

modulesarray=('_collectionsmodule' 'operator' 'itertoolsmodule' '_struct' 'mathmodule' 'binascii' 'timemodule' 'cStringIO' '_randommodule' 'arraymodule' 'socketmodule' '_functoolsmodule' 'cPickle' '_struct' 'selectmodule' 'arraymodule' 'unicodedata')
libsarray=('_collections' 'operator' 'itertools' '_struct' 'math' 'binascii' 'time' 'cStringIO' '_random' 'array' 'socket' '_functools' 'cPickle' '_struct' 'select' 'array' 'unicodedata')

echo Compiling...
length=${#libsarray[@]}
for (( i = 0; i < length; i++ ));
do
        x86_64-nacl-gcc -DPY_FORMAT_LONG_LONG=ll -std=c99 -fPIC -fno-strict-aliasing -march=x86-64 -mtune=generic -O2 -pipe -DNDEBUG -I. -IInclude -I./Include -c Modules/${modulesarray[i]}.c -o build/${modulesarray[i]}.o
done

echo Building libraries...
for (( i = 0; i < length; i++ ));
do
        x86_64-nacl-gcc -pthread -shared -Wl,-O1 -Wl,-Bsymbolic-functions -std=c99 build/${modulesarray[i]}.o -L. -lpython2.7 -o build/lib/${libsarray[i]}.so
done

echo Copying files...
for (( i = 0; i < length; i++ ));
do
        lindfs cp /home/lind/lind_project/tests/applications/python/build/lib/${libsarray[i]}.so /usr/local/lib/python2.7/lib-dynload/${libsarray[i]}.so
done
lindfs cp /home/lind/lind_project/tests/applications/python/libpython2.7.so.1.0 /lib/glibc/libpython2.7.so.1.0

echo Compiling special cases:
echo Datetime...
x86_64-nacl-gcc -DPY_FORMAT_LONG_LONG=ll -std=c99 -fPIC -fno-strict-aliasing -march=x86-64 -mtune=generic -O2 -pipe -DNDEBUG -I. -IInclude -I./Include -c Modules/datetimemodule.c -o build/datetimemodule.o
x86_64-nacl-gcc -pthread -shared -Wl,-O1 -Wl,-Bsymbolic-functions -std=c99 build/datetimemodule.o build/timemodule.o -L. -lpython2.7 -o build/lib/datetime.so
lindfs cp /home/lind/lind_project/tests/applications/python/build/lib/datetime.so /usr/local/lib/python2.7/lib-dynload/datetime.so

echo _io...
 export FNAME=bufferedio
 x86_64-nacl-gcc -DPY_FORMAT_LONG_LONG=ll -std=c99 -fPIC -fno-strict-aliasing -march=x86-64 -mtune=generic -O2 -pipe -DNDEBUG -I. -IInclude -I./Include -IModules/_io -c Modules/_io/$FNAME.c -o build/$FNAME.o
 export FNAME=bytesio
 x86_64-nacl-gcc -DPY_FORMAT_LONG_LONG=ll -std=c99 -fPIC -fno-strict-aliasing -march=x86-64 -mtune=generic -O2 -pipe -DNDEBUG -I. -IInclude -I./Include -IModules/_io -c Modules/_io/$FNAME.c -o build/$FNAME.o
 export FNAME=fileio
 x86_64-nacl-gcc -DPY_FORMAT_LONG_LONG=ll -std=c99 -fPIC -fno-strict-aliasing -march=x86-64 -mtune=generic -O2 -pipe -DNDEBUG -I. -IInclude -I./Include -IModules/_io -c Modules/_io/$FNAME.c -o build/$FNAME.o
 export FNAME=iobase
 x86_64-nacl-gcc -DPY_FORMAT_LONG_LONG=ll -std=c99 -fPIC -fno-strict-aliasing -march=x86-64 -mtune=generic -O2 -pipe -DNDEBUG -I. -IInclude -I./Include -IModules/_io -c Modules/_io/$FNAME.c -o build/$FNAME.o
 export FNAME=_iomodule
 x86_64-nacl-gcc -DPY_FORMAT_LONG_LONG=ll -std=c99 -fPIC -fno-strict-aliasing -march=x86-64 -mtune=generic -O2 -pipe -DNDEBUG -I. -IInclude -I./Include -IModules/_io -c Modules/_io/$FNAME.c -o build/$FNAME.o
 export FNAME=stringio
 x86_64-nacl-gcc -DPY_FORMAT_LONG_LONG=ll -std=c99 -fPIC -fno-strict-aliasing -march=x86-64 -mtune=generic -O2 -pipe -DNDEBUG -I. -IInclude -I./Include -IModules/_io -c Modules/_io/$FNAME.c -o build/$FNAME.o
 export FNAME=textio
 x86_64-nacl-gcc -DPY_FORMAT_LONG_LONG=ll -std=c99 -fPIC -fno-strict-aliasing -march=x86-64 -mtune=generic -O2 -pipe -DNDEBUG -I. -IInclude -I./Include -IModules/_io -c Modules/_io/$FNAME.c -o build/$FNAME.o
 
 x86_64-nacl-gcc -pthread -shared -Wl,-O1 -Wl,-Bsymbolic-functions -std=c99 build/bufferedio.o build/bytesio.o build/fileio.o build/iobase.o build/_iomodule.o build/stringio.o build/textio.o -L. -lpython2.7 -o build/lib/_io.so
 lindfs cp /home/lind/lind_project/tests/applications/python/build/lib/_io.so /usr/local/lib/python2.7/lib-dynload/_io.so
 
 echo zlib...
 cd /home/lind/lind_project/tests/applications/python/Modules/zlib
 ./bootstrap_nacl
 cd /home/lind/lind_project/tests/applications/python/
 x86_64-nacl-gcc -DPY_FORMAT_LONG_LONG=ll -std=c99 -fPIC -fno-strict-aliasing -march=x86-64 -mtune=generic -O2 -pipe -DNDEBUG -I. -IInclude -I./Include -I/home/lind/lind_project/tests/applications/python/Modules/zlib/ -c Modules/zlibmodule.c -o build/zlibmodule.o
 x86_64-nacl-gcc -pthread -shared -Wl,-O1 -Wl,-Bsymbolic-functions -std=c99 build/zlibmodule.o -L. -LModules/zlib -lpython2.7 -lz -o build/lib/zlib.so
 lindfs cp /home/lind/lind_project/tests/applications/python/build/lib/zlib.so /usr/local/lib/python2.7/lib-dynload/zlib.so
 lindfs cp /home/lind/lind_project/tests/applications/python/Modules/zlib/libz.so.1.2.3 /lib/glibc/libz.so.1

echo _ssl and _hashlib...
x86_64-nacl-gcc -c Modules/_ssl.c -o build/_ssl.o -DPY_FORMAT_LONG_LONG=ll -std=c99 -fPIC -fno-strict-aliasing -march=x86-64 -mtune=generic -O2 -pipe -DNDEBUG -I. -IInclude -I./Include -I/home/lind/lind_project/tests/applications/openssl/include/
x86_64-nacl-gcc build/_ssl.o -o build/lib/_ssl.so -pthread -shared -Wl,-O1 -Wl,-Bsymbolic-functions -std=c99 -L. -L../openssl/ -lpython2.7 -lssl -lcrypto
lindfs cp /home/lind/lind_project/tests/applications/python/build/lib/_ssl.so /usr/local/lib/python2.7/lib-dynload/_ssl.so

x86_64-nacl-gcc -c Modules/_hashopenssl.c -o build/_hashopenssl.o -DPY_FORMAT_LONG_LONG=ll -std=c99 -fPIC -fno-strict-aliasing -march=x86-64 -mtune=generic -O2 -pipe -DNDEBUG -I. -IInclude -I./Include -I/home/lind/lind_project/tests/applications/openssl/include/
x86_64-nacl-gcc build/_hashopenssl.o -o build/lib/_hashlib.so -pthread -shared -Wl,-O1 -Wl,-Bsymbolic-functions -std=c99 -L. -L../openssl/ -lpython2.7 -lssl -lcrypto
lindfs cp /home/lind/lind_project/tests/applications/python/build/lib/_hashlib.so /usr/local/lib/python2.7/lib-dynload/_hashlib.so

lindfs cp /home/lind/lind_project/tests/applications/openssl/libcrypto.so.1.0.0 /lib/glibc/libcrypto.so.1.0.0
lindfs cp /home/lind/lind_project/tests/applications/openssl/libssl.so.1.0.0 /lib/glibc/libssl.so.1.0.0