#!/bin/bash

cd /home/lind/lind_project/tests/applications/nginx

./auto/configure
make
make install DESTDIR=/home/lind/lind_project/fake_fs

touch /home/lind/lind_project/fake_fs/usr/local/nginx/logs/access.log 
#lindfs cp /home/lind/lind_project/tmp/usr/local/nginx/ /usr/local/nginx
#lindfs cp /home/lind/lind_project/tests/applications/nginx/objs/nginx /bin/nginx

