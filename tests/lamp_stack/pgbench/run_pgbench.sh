#!/bin/bash

/usr/local/pgsql/bin/postgres -F -c listen_addresses='' -D /usr/local/pgsql/data/ &
sleep 60
/usr/local/pgsql/bin/pgbench -i -U lind postgres
echo "PGBENCH -i -U COMPLETE"
/usr/local/pgsql/bin/pgbench -U lind postgres
echo "PGBENCH COMPLETE"
