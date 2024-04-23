echo "Starting...";

mkdir -p /home/lind/lind_project/tests/applications/python/build/lib

modulesarray=('_collectionsmodule' 'operator' 'itertoolsmodule' '_struct' 'mathmodule' 'binascii' 'timemodule' 'cStringIO' '_randommodule' 'arraymodule' 'socketmodule' '_functoolsmodule' 'cPickle' '_struct' 'selectmodule' 'arraymodule' 'unicodedata' 'fcntlmodule' 'grpmodule')
libsarray=('_collections' 'operator' 'itertools' '_struct' 'math' 'binascii' 'time' 'cStringIO' '_random' 'array' '_socket' '_functools' 'cPickle' '_struct' 'select' 'array' 'unicodedata' 'fcntl' 'grp')

echo Compiling...
for var in "${modulesarray[@]}"
do
    x86_64-nacl-gcc -DPY_FORMAT_LONG_LONG=ll -std=c99 -fPIC -fno-strict-aliasing -march=x86-64 -mtune=generic -O2 -pipe -DNDEBUG -I. -IInclude -I./Include -c Modules/$var.c -o build/$var.o
done

echo Building libraries...
length=${#libsarray[@]}
for (( i = 0; i < length; i++ ));
do
    x86_64-nacl-gcc -pthread -shared -Wl,-O1 -Wl,-Bsymbolic-functions -std=c99 build/${modulesarray[i]}.o -L. -lpython2.7 -o build/lib/${libsarray[i]}.so
done

echo Compiling special cases:
echo Datetime...
x86_64-nacl-gcc -DPY_FORMAT_LONG_LONG=ll -std=c99 -fPIC -fno-strict-aliasing -march=x86-64 -mtune=generic -O2 -pipe -DNDEBUG -I. -IInclude -I./Include -c Modules/datetimemodule.c -o build/datetimemodule.o
x86_64-nacl-gcc -pthread -shared -Wl,-O1 -Wl,-Bsymbolic-functions -std=c99 build/datetimemodule.o build/timemodule.o -L. -lpython2.7 -o build/lib/datetime.so

echo _io...
ioarray=('bufferedio' 'bytesio' 'fileio' 'iobase' '_iomodule' 'stringio' 'textio')
for iomodule in "${ioarray[@]}"
do
    x86_64-nacl-gcc -DPY_FORMAT_LONG_LONG=ll -std=c99 -fPIC -fno-strict-aliasing -march=x86-64 -mtune=generic -O2 -pipe -DNDEBUG -I. -IInclude -I./Include -IModules/_io -c Modules/_io/$iomodule.c -o build/$iomodule.o
done
x86_64-nacl-gcc -pthread -shared -Wl,-O1 -Wl,-Bsymbolic-functions -std=c99 build/bufferedio.o build/bytesio.o build/fileio.o build/iobase.o build/_iomodule.o build/stringio.o build/textio.o -L. -lpython2.7 -o build/lib/_io.so

echo _ctypes...
ctypesarray=('_ctypes' 'callbacks'  'callproc'  'cfield' 'malloc_closure' 'stgdict')
cd /home/lind/lind_project/tests/applications/python/Modules/_ctypes/libffi/
./bootstrap_nacl
cd /home/lind/lind_project/tests/applications/python/
for ctypesmodule in "${ctypesarray[@]}"
do
    x86_64-nacl-gcc -DPY_FORMAT_LONG_LONG=ll -std=c99 -fPIC -fno-strict-aliasing -march=x86-64 -mtune=generic -O2 -pipe -DNDEBUG -I. -IInclude -I./Include -IModules/_ctypes -IModules/_ctypes/libffi/include/ -c Modules/_ctypes/$ctypesmodule.c -o build/$ctypesmodule.o
done
cp Modules/_ctypes/libffi/libffi.so build/lib/libffi.so
x86_64-nacl-gcc -pthread -shared -Wl,-O1 -Wl,-Bsymbolic-functions -std=c99 build/_ctypes.o build/callbacks.o  build/callproc.o  build/cfield.o build/malloc_closure.o build/stgdict.o -L. -Lbuild/lib -lpython2.7 -lffi -o build/lib/_ctypes.so

echo zlib...
cd /home/lind/lind_project/tests/applications/python/Modules/zlib
./bootstrap_nacl
cd /home/lind/lind_project/tests/applications/python/
x86_64-nacl-gcc -DPY_FORMAT_LONG_LONG=ll -std=c99 -fPIC -fno-strict-aliasing -march=x86-64 -mtune=generic -O2 -pipe -DNDEBUG -I. -IInclude -I./Include -I/home/lind/lind_project/tests/applications/python/Modules/zlib/ -c Modules/zlibmodule.c -o build/zlibmodule.o
x86_64-nacl-gcc -pthread -shared -Wl,-O1 -Wl,-Bsymbolic-functions -std=c99 build/zlibmodule.o -L. -LModules/zlib -lpython2.7 -lz -o build/lib/zlib.so

echo _ssl and _hashlib...
x86_64-nacl-gcc -c Modules/_ssl.c -o build/_ssl.o -DPY_FORMAT_LONG_LONG=ll -std=c99 -fPIC -fno-strict-aliasing -march=x86-64 -mtune=generic -O2 -pipe -DNDEBUG -I. -IInclude -I./Include -I/home/lind/lind_project/tests/applications/openssl/include/
x86_64-nacl-gcc build/_ssl.o -o build/lib/_ssl.so -pthread -shared -Wl,-O1 -Wl,-Bsymbolic-functions -std=c99 -L. -L../openssl/ -lpython2.7 -lssl -lcrypto
x86_64-nacl-gcc -c Modules/_hashopenssl.c -o build/_hashopenssl.o -DPY_FORMAT_LONG_LONG=ll -std=c99 -fPIC -fno-strict-aliasing -march=x86-64 -mtune=generic -O2 -pipe -DNDEBUG -I. -IInclude -I./Include -I/home/lind/lind_project/tests/applications/openssl/include/
x86_64-nacl-gcc build/_hashopenssl.o -o build/lib/_hashlib.so -pthread -shared -Wl,-O1 -Wl,-Bsymbolic-functions -std=c99 -L. -L../openssl/ -lpython2.7 -lssl -lcrypto
