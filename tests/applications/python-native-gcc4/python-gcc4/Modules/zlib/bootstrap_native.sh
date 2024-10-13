#!/bin/bash

if [ -f /etc/lsb-release ]; then
    . /etc/lsb-release
    if [ "$DISTRIB_ID" = "Ubuntu" ]; then
        export LIBRARY_PATH=/usr/lib/x86_64-linux-gnu
    fi
fi

export CC=/usr/local/gcc-4.4.3/bin/gcc
export CXX=/usr/local/gcc-4.4.3/bin/g++

export CFLAGS='-g -fno-pie -fPIC'
export CXXFLAGS='-g -fno-pie'
export LDFLAGS='-g -fno-pie'
export PATH="/usr/bin:/usr/sbin:/bin:/sbin:$PATH"
export PREFIX="/home/lind/lind_project/lind/lindenv/sdk/toolchain/linux_x86_glibc/x86_64-nacl"


./configure --shared #--prefix="$PREFIX" --exec_prefix="$PREFIX" --libdir="$PREFIX/lib" # "$@"

make 
