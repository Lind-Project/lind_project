#!/bin/bash

/usr/local/pgsql/bin/postgres -F -c listen_addresses='' -D /usr/local/pgsql/data/ &
sleep 15
echo "postgres ready"
/bin/python /init_table.py
sleep 3
echo "table ready"
for i in {1..10}; do
	/bin/python /app.py
done
