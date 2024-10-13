#!/bin/bash

if [ -f /etc/lsb-release ]; then
    . /etc/lsb-release
    if [ "$DISTRIB_ID" = "Ubuntu" ]; then
        export LIBRARY_PATH=/usr/lib/x86_64-linux-gnu
    fi
fi

cd /home/lind/lind_project/tests/applications/postgres/

./configure CC=/usr/local/gcc-4.4.3/bin/gcc CXX=/usr/local/gcc-4.4.3/bin/g++
make
sudo make install
sudo mkdir -m 770 /usr/local/pgsql/data/
sudo chown lind:lind /usr/local/pgsql/data

export LC_ALL=C
/usr/local/pgsql/bin/initdb --username=lind --debug --no-sync --auth=trust -E UNICODE --locale=C -D /usr/local/pgsql/data
