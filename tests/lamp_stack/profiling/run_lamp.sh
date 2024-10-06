#!/bin/bash

/usr/local/pgsql/bin/postgres -F -c listen_addresses='' -D /usr/local/pgsql/data/ &
sleep 15
echo "postgres ready"
/bin/python /init_table.py
sleep 3
echo "table ready"
/usr/local/nginx/sbin/nginx -c /usr/local/nginx/conf/nginx_static.conf -p /usr/local/nginx/
sleep 5
echo "nginx ready"
/bin/python gunicornexec.py --bind unix:/tmp/gunicorn.sock wsgi:app 2>&1
sleep 5
echo "system ready"
