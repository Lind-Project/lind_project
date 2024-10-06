#!/bin/bash

if [ -f /etc/lsb-release ]; then
    . /etc/lsb-release
    if [ "$DISTRIB_ID" = "Ubuntu" ]; then
        export LIBRARY_PATH=/usr/lib/x86_64-linux-gnu
    fi
fi

cd /home/lind/lind_project/tests/applications/nginx
./auto/configure CC=/usr/local/gcc-4.4.3/bin/gcc CXX=/usr/local/gcc-4.4.3/bin/g++
make
sudo make install
sudo cp /home/lind/lind_project/src/scripts/nginx/nginx-conf/nginx.conf /usr/local/nginx/conf/nginx.conf
sudo cp /home/lind/lind_project/src/scripts/nginx/nginx-conf/nginx_static.conf /usr/local/nginx/conf/nginx_static.conf
sudo touch /usr/local/nginx/logs/access.log
sudo touch /usr/local/nginx/logs/error.log
