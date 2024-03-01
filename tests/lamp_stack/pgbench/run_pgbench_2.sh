#!/bin/bash

/bin/unlink /usr/local/pgsql/data/postmaster.pid
/usr/local/pgsql/bin/pg_resetwal -f /usr/local/pgsql/data/
/usr/local/pgsql/bin/pg_ctl -o "-c listen_addresses=''" -D /usr/local/pgsql/data/ start &
sleep 20
/usr/local/pgsql/bin/pgbench -i -U lind postgres
echo "PGBENCH -i -U COMPLETE"
/usr/local/pgsql/bin/pgbench -U lind postgres
echo "PGBENCH COMPLETE"
/usr/local/pgsql/bin/pg_ctl -D /usr/local/pgsql/data/ -m smart stop
echo "POSTGRES STOPPED"
