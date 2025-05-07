#!/bin/bash

export PATH=/usr/local/python-gcc4/bin/:$PATH
export LD_LIBRARY_PATH=/usr/local/python-gcc4/lib:/usr/local/pgsql/lib:$LD_LIBRARY_PATH
export PYTHONHOME="/usr/local/python-gcc4"
export PYTHONPATH="/usr/local/python-gcc4/lib/:/usr/local/python-gcc4/lib/python2.7/site-packages"

/usr/local/pgsql/bin/postgres -F -d 0 -c listen_addresses='' -D /usr/local/pgsql/data/ &
sleep 15
echo "postgres ready"

/usr/local/python-gcc4/bin/python init_table.py
sleep 3
echo "table ready"

sudo cp -f ./nginx.conf /usr/local/nginx/conf/nginx.conf
sudo /usr/local/nginx/sbin/nginx -c /usr/local/nginx/conf/nginx.conf -p /usr/local/nginx/
sleep 5
echo "nginx ready"

./tmp/fioapp
sleep 5
echo "system ready"
