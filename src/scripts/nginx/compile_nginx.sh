#!/bin/bash

cd /home/lind/lind_project/tests/applications/nginx

./bootstrap_nacl

make install DESTDIR=/home/lind/lind_project/lind/tmp

touch /home/lind/lind_project/lind/tmp/usr/local/nginx/logs/access.log 

