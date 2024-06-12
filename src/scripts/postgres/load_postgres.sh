#!/bin/bash
# copies postgres in lindfs.

# we need to recopy glibc files to /lib
# lindfs cp /home/lind/lind_project/lind/lindenv/sdk/toolchain/linux_x86_glibc/x86_64-nacl/lib/ lib/ 
cp -r /home/lind/lind_project/lind/lindenv/sdk/toolchain/linux_x86_glibc/x86_64-nacl/lib/ /home/lind/lind_project/src/safeposix-rust/tmp/lib/ 

echo "Copying Postgres"

# lindfs cp /home/lind/lind_project/lind/tmp/usr/local/pgsql /usr/local/pgsql
# lindfs cp /home/lind/lind_project/tests/applications/postgres/src/interfaces/libpq/libpq.so.5.13 /lib/glibc/libpq.so.5
# lindfs cp /home/lind/lind_project/lind/tmp/usr/local/pgsql/bin/postgres bin/postgres
# lindfs cp /home/lind/lind_project/src/scripts/postgres/init_postgres.sh init_postgres.sh
# lindfs cp /home/lind/lind_project/src/scripts/postgres/run_pgsql.sh run_pgsql.sh
cp -r /home/lind/lind_project/lind/tmp/usr/local/pgsql /home/lind/lind_project/src/safeposix-rust/tmp/usr/local/pgsql
cp /home/lind/lind_project/tests/applications/postgres/src/interfaces/libpq/libpq.so.5.13 /home/lind/lind_project/src/safeposix-rust/tmp/lib/glibc/libpq.so.5
cp /home/lind/lind_project/lind/tmp/usr/local/pgsql/bin/postgres /home/lind/lind_project/src/safeposix-rust/tmp/bin/postgres
cp /home/lind/lind_project/src/scripts/postgres/init_postgres.sh /home/lind/lind_project/src/safeposix-rust/tmp/init_postgres.sh
cp /home/lind/lind_project/src/scripts/postgres/run_pgsql.sh /home/lind/lind_project/src/safeposix-rust/tmp/run_pgsql.sh

# lindfs mkdir /tmp
mkdir /home/lind/lind_project/src/safeposix-rust/tmp/tmp/
