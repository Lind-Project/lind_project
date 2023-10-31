#!/bin/bash

cd /home/lind/lind_project/tests/applications/nginx
./auto/configure
make
make install DESTDIR=/home/lind/nginx
cp /home/lind/lind_project/src/scripts/nginx/nginx-conf/nginx.conf /home/lind/nginx/usr/local/nginx/conf/nginx.conf
touch /home/lind/nginx/usr/local/nginx/logs/access.log
touch /home/lind/nginx/usr/local/nginx/logs/error.log
