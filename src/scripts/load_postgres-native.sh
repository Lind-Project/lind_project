#!/bin/bash
# Builds postgres and copies the library in lindfs.

echo "Compiling Postgres"
cd /home/lind/lind_project/tests/applications/postgres/
./configure #--enable-shared;

echo "Installing Postgres" # This script will be re-adjusted after postgres is fully usable.
make
make install DESTDIR=/home/lind/lind_project/fake_fs
#cp -r /home/lind/lind_project/tmp/usr/local/pgsql /home/lind/lind_project/fake_fs/usr/local/pgsql

echo "Copying Postgres"
cp /home/lind/lind_project/tests/applications/postgres/src/interfaces/libpq/libpq.so.5.13 /home/lind/lind_project/fake_fs/lib/libpq.so.5

