#!/bin/bash

export PATH=/usr/local/python-gcc4/bin/:$PATH

/usr/local/pgsql/bin/postgres -F -d 0 -c listen_addresses='' -D /usr/local/pgsql/data/ &
sleep 15
echo "postgres ready"
/usr/local/python-gcc4/bin/python flask_app/init_table.py
sleep 3
echo "table ready"
sudo /usr/local/nginx/sbin/nginx -c /usr/local/nginx/conf/nginx.conf -p /usr/local/nginx/
sleep 5
echo "nginx ready"
cd flask_app/
/usr/local/python-gcc4/bin/python gunicornexec.py --bind=unix:/tmp/gunicorn.sock wsgi:app
sleep 5
echo "system ready"
