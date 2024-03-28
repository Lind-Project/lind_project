#!/bin/bash

/usr/local/nginx/sbin/nginx -c /usr/local/nginx/conf/nginx.conf -p /usr/local/nginx/
sleep 5
echo "nginx ready"
/bin/python gunicornexec.py --bind 0.0.0.0:8000 wsgi_no_pg:app 2>&1
sleep 5
echo "system ready"
