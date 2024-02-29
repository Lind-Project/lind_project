#!/bin/bash

lindfs cp /home/lind/lind_project/lind/tmp/usr/local/nginx/ /usr/local/nginx
lindfs cp /home/lind/lind_project/lind/tmp/usr/local/nginx/sbin/nginx /bin/nginx
lindfs cp /home/lind/lind_project/src/scripts/nginx/nginx-conf/nginx.conf /usr/local/nginx/conf/nginx.conf
lindfs cp /home/lind/lind_project/src/scripts/nginx/nginx-conf/nginx_static.conf /usr/local/nginx/conf/nginx_static.conf
lindfs cp /home/lind/lind_project/src/scripts/nginx/sites/sites-available/myproject /etc/nginx/sites-available/myproject
lindfs cp /home/lind/lind_project/src/scripts/nginx/sites/sites-enabled/myproject /etc/nginx/sites-enabled/myproject
