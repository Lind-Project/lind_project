#!/bin/bash

if [ -f /etc/lsb-release ]; then
    . /etc/lsb-release
    if [ "$DISTRIB_ID" = "Ubuntu" ]; then
        export LIBRARY_PATH=/usr/lib/x86_64-linux-gnu
    fi
fi

/usr/local/gcc-4.4.3/bin/gcc scripts/read.c -o scripts/readpipe -std=gnu99 -O3
/usr/local/gcc-4.4.3/bin/gcc scripts/write.c -o scripts/writepipe -std=gnu99 -O3
