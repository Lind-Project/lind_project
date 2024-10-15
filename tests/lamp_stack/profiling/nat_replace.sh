#!/bin/bash

export PATH=/usr/local/python-gcc4/bin/:$PATH
export PYTHONPATH=/usr/local/python-gcc4/lib-dynload:$PYTHONPATH
export LD_LIBRARY_PATH=/usr/local/pgsql/lib/:$LD_LIBRARY_PATH

/usr/local/pgsql/bin/postgres -F -d 0 -c listen_addresses='' -D /usr/local/pgsql/data/ &
sleep 15
echo "postgres ready"
cd flask_app/
/usr/local/python-gcc4/bin/python replace_init.py
sleep 3
echo "table ready"
for i in {0..10}; do
    /usr/local/python-gcc4/bin/python replace_app.py
done
