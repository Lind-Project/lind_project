#!/bin/bash

/usr/local/pgsql/bin/postgres -F -c listen_addresses='' -D /usr/local/pgsql/data/ &
sleep 15
echo "postgres ready"
/bin/python /replace_init.py
sleep 3
echo "table ready"
for i in {0..10}; do
    /bin/python replace_app.py
done
