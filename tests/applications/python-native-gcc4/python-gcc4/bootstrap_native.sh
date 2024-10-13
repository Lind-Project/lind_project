#!/bin/bash

if [ -f /etc/lsb-release ]; then
    . /etc/lsb-release
    if [ "$DISTRIB_ID" = "Ubuntu" ]; then
        export LIBRARY_PATH=/usr/lib/x86_64-linux-gnu
    fi
fi

cp -r /home/lind/lind_project/tests/applications/python/python-native .

cd python-native

./configure #build a native version of Python to get pgen from
touch Include/Python-ast.h Python/Python-ast.c
make Parser/pgen #build a native version of Python to get pgen from

cd ..

if [[ "$*" =~ (^|[[:blank:]])(-h|--help)([[:blank:]]|$) ]]; then
    ./configure --help
    exit 1
fi

export CC=/usr/local/gcc-4.4.3/bin/gcc
export CXX=/usr/local/gcc-4.4.3/bin/g++
# export LD="x86_64-nacl-ld -shared"
export CFLAGS='-g -e -fPIC -fno-pie -DPY_FORMAT_LONG_LONG="ll" -O3 -std=c99'
export CXXFLAGS='-g -fPIC -fno-pie -O3'
export LDFLAGS='-g -fno-pie -O3'
# export PATH="/usr/bin:/usr/sbin:/bin:/sbin:$PATH"

if [[ ! -e ./configure ]]; then
    ./autogen.sh
fi

./configure --enable-shared "$@"

cp "./Modules/Setup.dist"  "./Modules/Setup"

touch Include/Python-ast.h Python/Python-ast.c

make #will fail

cp python-native/Parser/pgen Parser/pgen

chmod +x Parser/pgen

make
