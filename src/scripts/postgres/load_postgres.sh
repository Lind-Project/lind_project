#!/bin/bash
# copies postgres in lindfs.

# we need to recopy glibc files to /lib
lindfs cp /home/lind/lind_project/lind/lindenv/sdk/toolchain/linux_x86_glibc/x86_64-nacl/lib/ lib/ 

echo "Copying Postgres"

lindfs cp /home/lind/lind_project/lind/tmp/usr/local/pgsql /usr/local/pgsql
lindfs cp /home/lind/lind_project/tests/applications/postgres/src/interfaces/libpq/libpq.so.5.13 /lib/glibc/libpq.so.5
lindfs cp /home/lind/lind_project/lind/tmp/usr/local/pgsql/bin/postgres bin/postgres
lindfs cp /home/lind/lind_project/src/scripts/postgres/init_postgres.sh init_postgres.sh
lindfs cp /home/lind/lind_project/src/scripts/postgres/run_pgsql.sh run_pgsql.sh
