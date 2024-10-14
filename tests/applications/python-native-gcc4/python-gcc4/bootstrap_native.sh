#!/bin/bash

if [ -f /etc/lsb-release ]; then
    . /etc/lsb-release
    if [ "$DISTRIB_ID" = "Ubuntu" ]; then
        export LIBRARY_PATH=/usr/lib/x86_64-linux-gnu
    fi
fi

export CC=/usr/local/gcc-4.4.3/bin/gcc
export CXX=/usr/local/gcc-4.4.3/bin/g++
export CFLAGS='-g -e -fPIC -fno-pie -DPY_FORMAT_LONG_LONG="ll" -O3 -std=c99'
export CXXFLAGS='-g -fPIC -fno-pie -O3'
export LDFLAGS='-g -fno-pie -O3'

./configure --enable-shared "$@"
make
