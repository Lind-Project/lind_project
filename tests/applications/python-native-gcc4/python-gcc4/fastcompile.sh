if [ -f /etc/lsb-release ]; then
    . /etc/lsb-release
    if [ "$DISTRIB_ID" = "Ubuntu" ]; then
        export LIBRARY_PATH=/usr/lib/x86_64-linux-gnu
    fi
fi

mkdir -p /home/lind/lind_project/tests/applications/python-g/usr/local/gcc-4.4.3/bin/gcc4/build/lib


modulesarray=('_collectionsmodule' 'operator' 'itertoolsmodule' '_struct' 'mathmodule' 'binascii' 'timemodule' 'cStringIO' '_randommodule' 'arraymodule' 'socketmodule' '_functoolsmodule' 'cPickle' '_struct' 'selectmodule' 'arraymodule' 'unicodedata' 'fcntlmodule' 'grpmodule')
libsarray=('_collections' 'operator' 'itertools' '_struct' 'math' 'binascii' 'time' 'cStringIO' '_random' 'array' '_socket' '_functools' 'cPickle' '_struct' 'select' 'array' 'unicodedata' 'fcntl' 'grp')

echo Compiling...
for var in "${modulesarray[@]}"
do
    /usr/local/gcc-4.4.3/bin/gcc -DPY_FORMAT_LONG_LONG=ll -std=c99 -fPIC -fno-strict-aliasing -march=x86-64 -mtune=generic -O2 -pipe -DNDEBUG -I. -IInclude -I./Include -c Modules/$var.c -o build/$var.o
done

echo Building libraries...
length=${#libsarray[@]}
for (( i = 0; i < length; i++ ));
do
    /usr/local/gcc-4.4.3/bin/gcc -pthread -shared -Wl,-O1 -Wl,-Bsymbolic-functions -std=c99 build/${modulesarray[i]}.o -L. -lpython2.7 -o build/lib/${libsarray[i]}.so
done

echo Compiling special cases:
echo Datetime...
/usr/local/gcc-4.4.3/bin/gcc -DPY_FORMAT_LONG_LONG=ll -std=c99 -fPIC -fno-strict-aliasing -march=x86-64 -mtune=generic -O2 -pipe -DNDEBUG -I. -IInclude -I./Include -c Modules/datetimemodule.c -o build/datetimemodule.o
/usr/local/gcc-4.4.3/bin/gcc -pthread -shared -Wl,-O1 -Wl,-Bsymbolic-functions -std=c99 build/datetimemodule.o build/timemodule.o -L. -lpython2.7 -o build/lib/datetime.so

echo _io...
ioarray=('bufferedio' 'bytesio' 'fileio' 'iobase' '_iomodule' 'stringio' 'textio')
for iomodule in "${ioarray[@]}"
do
    /usr/local/gcc-4.4.3/bin/gcc -DPY_FORMAT_LONG_LONG=ll -std=c99 -fPIC -fno-strict-aliasing -march=x86-64 -mtune=generic -O2 -pipe -DNDEBUG -I. -IInclude -I./Include -IModules/_io -c Modules/_io/$iomodule.c -o build/$iomodule.o
done
/usr/local/gcc-4.4.3/bin/gcc -pthread -shared -Wl,-O1 -Wl,-Bsymbolic-functions -std=c99 build/bufferedio.o build/bytesio.o build/fileio.o build/iobase.o build/_iomodule.o build/stringio.o build/textio.o -L. -lpython2.7 -o build/lib/_io.so

echo _ctypes...
ctypesarray=('_ctypes' 'callbacks'  'callproc'  'cfield' 'malloc_closure' 'stgdict')
cd /home/lind/lind_project/tests/applications/python-native-gcc4/python-gcc4/Modules/_ctypes/libffi/
./bootstrap_native.sh
cd /home/lind/lind_project/tests/applications/python-native-gcc4/python-gcc4/
for ctypesmodule in "${ctypesarray[@]}"
do
    /usr/local/gcc-4.4.3/bin/gcc -DPY_FORMAT_LONG_LONG=ll -std=c99 -fPIC -fno-strict-aliasing -march=x86-64 -mtune=generic -O2 -pipe -DNDEBUG -I. -IInclude -I./Include -IModules/_ctypes -IModules/_ctypes/libffi/include/ -c Modules/_ctypes/$ctypesmodule.c -o build/$ctypesmodule.o
done
cp Modules/_ctypes/libffi/libffi.so build/lib/libffi.so
/usr/local/gcc-4.4.3/bin/gcc -pthread -shared -Wl,-O1 -Wl,-Bsymbolic-functions -std=c99 build/_ctypes.o build/callbacks.o  build/callproc.o  build/cfield.o build/malloc_closure.o build/stgdict.o -L. -Lbuild/lib -lpython2.7 -lffi -o build/lib/_ctypes.so

echo zlib...
cd /home/lind/lind_project/tests/applications/python-native-gcc4/python-gcc4/Modules/zlib
./bootstrap_native.sh
cd /home/lind/lind_project/tests/applications/python-native-gcc4/python-gcc4/
/usr/local/gcc-4.4.3/bin/gcc -DPY_FORMAT_LONG_LONG=ll -std=c99 -fPIC -fno-strict-aliasing -march=x86-64 -mtune=generic -O2 -pipe -DNDEBUG -I. -IInclude -I./Include -I/home/lind/lind_project/tests/applications/python-native-gcc4/python-gcc4/Modules/zlib/ -c Modules/zlibmodule.c -o build/zlibmodule.o
/usr/local/gcc-4.4.3/bin/gcc -pthread -shared -Wl,-O1 -Wl,-Bsymbolic-functions -std=c99 build/zlibmodule.o -L. -LModules/zlib -lpython2.7 -lz -o build/lib/zlib.so

echo _ssl and _hashlib...
/usr/local/gcc-4.4.3/bin/gcc -c Modules/_ssl.c -o build/_ssl.o -DPY_FORMAT_LONG_LONG=ll -std=c99 -fPIC -fno-strict-aliasing -march=x86-64 -mtune=generic -O2 -pipe -DNDEBUG -I. -IInclude -I./Include -I/home/lind/lind_project/tests/applications/python-native-gcc4/openssl/include/
/usr/local/gcc-4.4.3/bin/gcc build/_ssl.o -o build/lib/_ssl.so -pthread -shared -Wl,-O1 -Wl,-Bsymbolic-functions -std=c99 -L. -L../openssl/ -lpython2.7 -lssl -lcrypto
/usr/local/gcc-4.4.3/bin/gcc -c Modules/_hashopenssl.c -o build/_hashopenssl.o -DPY_FORMAT_LONG_LONG=ll -std=c99 -fPIC -fno-strict-aliasing -march=x86-64 -mtune=generic -O2 -pipe -DNDEBUG -I. -IInclude -I./Include -I/home/lind/lind_project/tests/applications/python-native-gcc4/openssl/include/
/usr/local/gcc-4.4.3/bin/gcc build/_hashopenssl.o -o build/lib/_hashlib.so -pthread -shared -Wl,-O1 -Wl,-Bsymbolic-functions -std=c99 -L. -L../openssl/ -lpython2.7 -lssl -lcrypto


