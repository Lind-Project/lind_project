#!/bin/bash
# Builds postgres and copies the library in lindfs.

echo "Prerequisite: Coreutils-bash as sh."
cd /home/lind/lind_project/src/scripts
./load_coreutils.sh
lindfs cp /home/lind/lind_project/tests/applications/bash/bash /bin/sh

echo "Compiling Postgres"
cd /home/lind/lind_project/tests/applications/postgres/
./bootstrap_nacl;

echo "Installing Postgres" # This script will be re-adjusted after postgres is fully usable.
make install DESTDIR=/home/lind/lind_project/tmp
lindfs cp /home/lind/lind_project/tmp/usr/local/pgsql /usr/local/pgsql
rm -rf /home/lind/lind_project/tmp

echo "Copying Postgres"
lindfs cp /home/lind/lind_project/tests/applications/postgres/src/interfaces/libpq/libpq.so.5.13 /lib/glibc/libpq.so.5

echo "Copying Support files"

./load_confs.sh
