#!/bin/bash

echo "Compiling native test binaries"
gcc server.c -o server -std=gnu99 -lpthread -lrt
gcc client.c -o client -std=gnu99 -lpthread -lrt

echo "Compiling lind test binaries"
x86_64-nacl-gcc server.c -o server.nexe -std=gnu99 -lpthread -lrt
x86_64-nacl-gcc client.c -o client.nexe -std=gnu99 -lpthread -lrt

cd /home/lind/lind_project/tests/lamp_stack/profiling/flask_app/
python2 gen_static_html.py -s 17
cd /home/lind/lind_project/tests/lamp_stack/profiling/nginx_simple_test/
cp ../flask_app/static.html static.html
lindfs cp /home/lind/lind_project/tests/lamp_stack/profiling/nginx_simple_test/server.nexe /server
lindfs cp /home/lind/lind_project/tests/lamp_stack/profiling/nginx_simple_test/client.nexe /client
lindfs cp /home/lind/lind_project/tests/lamp_stack/profiling/nginx_simple_test/static.html /static.html
