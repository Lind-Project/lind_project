#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <filesize> <platform>"
    exit 1
fi

param=$1
platform=$2

/bin/python /home/lind/lind_project/tests/lamp_stack/profiling/flask_app/gen_static_html.py -s $param

if [ "$platform" == "lind" ]; then
    lindfs cp /home/lind/lind_project/tests/lamp_stack/profiling/flask_app/static.html /static.html
else
    cp /home/lind/lind_project/tests/lamp_stack/profiling/flask_app/static.html /home/lind/lind_project/static.html
fi
