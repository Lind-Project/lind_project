#!/bin/bash

# lindfs cp /home/lind/lind_project/lind/tmp/usr/local/nginx/ /usr/local/nginx
# lindfs cp /home/lind/lind_project/lind/tmp/usr/local/nginx/sbin/nginx /bin/nginx
# lindfs cp /home/lind/lind_project/src/scripts/nginx/nginx-conf/nginx.conf /usr/local/nginx/conf/nginx.conf
# lindfs cp /home/lind/lind_project/src/scripts/nginx/nginx-conf/nginx_static.conf /usr/local/nginx/conf/nginx_static.conf
# lindfs cp /home/lind/lind_project/src/scripts/nginx/sites/sites-available/myproject /etc/nginx/sites-available/myproject
# lindfs cp /home/lind/lind_project/src/scripts/nginx/sites/sites-enabled/myproject /etc/nginx/sites-enabled/myproject

cp -r /home/lind/lind_project/lind/tmp/usr/local/nginx/ /home/lind/lind_project/src/safeposix-rust/tmp/usr/local/nginx
cp /home/lind/lind_project/lind/tmp/usr/local/nginx/sbin/nginx /home/lind/lind_project/src/safeposix-rust/tmp/bin/nginx
mkdir -p /home/lind/lind_project/src/safeposix-rust/tmp/usr/local/nginx/conf
cp /home/lind/lind_project/src/scripts/nginx/nginx-conf/nginx.conf /home/lind/lind_project/src/safeposix-rust/tmp/usr/local/nginx/conf/nginx.conf
cp /home/lind/lind_project/src/scripts/nginx/nginx-conf/nginx_static.conf /home/lind/lind_project/src/safeposix-rust/tmp/usr/local/nginx/conf/nginx_static.conf
mkdir -p /home/lind/lind_project/src/safeposix-rust/tmp/etc/nginx/sites-available
cp /home/lind/lind_project/src/scripts/nginx/sites/sites-available/myproject /home/lind/lind_project/src/safeposix-rust/tmp/etc/nginx/sites-available/myproject
mkdir -p /home/lind/lind_project/src/safeposix-rust/tmp/etc/nginx/sites-enabled
cp /home/lind/lind_project/src/scripts/nginx/sites/sites-enabled/myproject /home/lind/lind_project/src/safeposix-rust/tmp/etc/nginx/sites-enabled/myproject