#!/bin/bash

cd /home/lind/lind_project/tests/applications/nginx
./auto/configure
make
sudo make install DESTDIR=/usr/local/nginx
cp /home/lind/lind_project/src/scripts/nginx/nginx-conf/nginx.conf /usr/local/nginx/conf/nginx.conf
touch /usr/local/nginx/logs/access.log
touch /usr/local/nginx/logs/error.log
