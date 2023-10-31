#!/bin/bash

cd /home/lind/lind_project/tests/applications/nginx
./auto/configure
make
sudo make install
sudo cp /home/lind/lind_project/tests/applications/nginx/conf/nginx.conf /usr/local/nginx/conf/nginx.conf
