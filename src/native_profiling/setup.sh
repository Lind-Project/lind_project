#!/bin/bash

export DB_USERNAME="lind"
export DB_PASSWORD="password"

postgres -d 0 -F -D pgsql/data/ &

nginx -p nginx -c nginx.conf

python2.7 gunicornexec.py --workers 8 --timeout 300 --backlog 2048 --worker-connections 16384 --max-requests 1024 --bind 0.0.0.0:8000 wsgi:app &
