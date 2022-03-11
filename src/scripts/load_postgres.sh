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

cp /etc/hosts /home/lind/lind_project/hosts
echo -e "127.0.0.1\tLind" >> /home/lind/lind_project/hosts
lindfs cp /home/lind/lind_project/hosts /etc/hosts # Adjusted as we also need Lind's ip as 127.0.0.1 in the list.
rm /home/lind/lind_project/hosts

lindfs cp /etc/resolv.conf /etc/resolv.conf
lindfs cp /etc/nsswitch.conf /etc/nsswitch.conf
lindfs cp /etc/host.conf /etc/host.conf
lindfs cp /usr/share/zoneinfo/America/New_York /etc/localtime # As we don't have /etc/localtime default in lind.

