#!/bin/bash

/usr/local/nginx/sbin/nginx -c /usr/local/nginx/conf/nginx_static.conf -p /usr/local/nginx/
sleep 5
echo "nginx ready"
