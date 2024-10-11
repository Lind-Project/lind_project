#!/bin/bash

/usr/local/pgsql/bin/postgres -F -d 0 -c listen_addresses='' -D /usr/local/pgsql/data/ &
sleep 15
echo "postgres ready"
cd flask_app/
/bin/python3 init_table.py
sleep 3
echo "table ready"
sudo /usr/local/nginx/sbin/nginx -c /usr/local/nginx/conf/nginx.conf -p /usr/local/nginx/
sleep 5
echo "nginx ready"
cd flask_app/
# /bin/python2.7 gunicornexec.py --bind=unix:/tmp/gunicorn.sock wsgi:app
/bin/python3 app.py
sleep 5
echo "system ready"
