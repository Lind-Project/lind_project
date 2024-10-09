#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <param>"
    exit 1
fi

param=$1

/bin/python /home/lind/lind_project/tests/lamp_stack/profiling/flask_app/gen_static_html.py -s $param

cp /home/lind/lind_project/tests/lamp_stack/profiling/flask_app/static.html /home/lind/lind_project/static.html

sudo /usr/local/nginx/sbin/nginx -c /usr/local/nginx/conf/nginx_static.conf -p /usr/local/nginx/
