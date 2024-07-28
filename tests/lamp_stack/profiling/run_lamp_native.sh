#!/bin/bash

/usr/local/pgsql/bin/postgres -F -d 0 -c listen_addresses='' -D /usr/local/pgsql/data/ &
sleep 15
echo "postgres ready"
/bin/python flask_app/init_table.py
sleep 3
echo "table ready"
/home/lind/nginx/usr/local/nginx/sbin/nginx -c /home/lind/nginx/usr/local/nginx/conf/nginx.conf -p /home/lind/nginx/usr/local/nginx/
sleep 5
echo "nginx ready"
cd flask_app/
/bin/python2.7 gunicornexec.py --bind=unix:/tmp/gunicorn.sock wsgi:app
sleep 5
echo "system ready"
