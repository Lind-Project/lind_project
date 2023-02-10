#!/bin/bash

/usr/local/pgsql/bin/postgres -F -d 5 -c listen_addresses='' -D /usr/local/pgsql/data/ &
sleep 90
echo "POSTGRES READY"
/bin/python /init_table.py
sleep 3
echo "system ready"
