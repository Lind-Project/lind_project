#!/bin/bash

/usr/local/pgsql/bin/pg_ctl -o "-F -c listen_addresses=''" -D /usr/local/pgsql/data/ start &
sleep 15
/usr/local/pgsql/bin/pgbench -i -U lind postgres
echo "PGBENCH -i -U COMPLETE"
/usr/local/pgsql/bin/pgbench -t 100000 -U lind postgres
echo "PGBENCH COMPLETE"
/usr/local/pgsql/bin/pg_ctl stop -D /usr/local/pgsql/data/ -m smart
echo "POSTGRES STOPPED"
