#!/bin/bash

/usr/local/pgsql/bin/postgres -F -c listen_addresses='' -D /usr/local/pgsql/data/ &
sleep 15
/usr/local/pgsql/bin/pgbench -i -U lind postgres
echo "PGBENCH -i -U COMPLETE"
/usr/local/pgsql/bin/pgbench -t 1000 -U lind postgres
echo "PGBENCH COMPLETE"
