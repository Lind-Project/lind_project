#!/bin/bash

cd  /home/lind/lind_project/tests/applications/nginx/

/home/lind/lind_project/tests/applications/nginx/bootstrap_nacl

make install DESTDIR=/home/lind/lind_project/tmp

lindfs mkdir /usr

lindfs mkdir /usr/local

mkdir /home/lind/lind_project/tmp/usr/local/nginx/logs

touch /home/lind/lind_project/tmp/usr/local/nginx/logs/access.log

lindfs cp /home/lind/lind_project/tmp/usr/local/nginx /usr/local/nginx

#rm -rf /home/lind/lind_project/tmp #Optional
