#!/bin/bash

mkdir -p /home/lind/lind_project/src/safeposix-rust/tmp/bin
mkdir -p /home/lind/lind_project/src/safeposix-rust/tmp/usr/local/
mkdir -p /home/lind/lind_project/src/safeposix-rust/tmp/etc

########################################## Postgres ##########################################

echo -e "Loading postgres to RawPOSIX"
# we need to recopy glibc files to /lib
cp -r /home/lind/lind_project/lind/lindenv/sdk/toolchain/linux_x86_glibc/x86_64-nacl/lib/ /home/lind/lind_project/src/safeposix-rust/tmp/lib/ 

echo "Copying Postgres"

cp -r /home/lind/lind_project/lind/tmp/usr/local/pgsql /home/lind/lind_project/src/safeposix-rust/tmp/usr/local/pgsql
cp /home/lind/lind_project/tests/applications/postgres/src/interfaces/libpq/libpq.so.5.13 /home/lind/lind_project/src/safeposix-rust/tmp/lib/glibc/libpq.so.5
cp /home/lind/lind_project/lind/tmp/usr/local/pgsql/bin/postgres /home/lind/lind_project/src/safeposix-rust/tmp/bin/postgres
cp /home/lind/lind_project/src/scripts/postgres/init_postgres.sh /home/lind/lind_project/src/safeposix-rust/tmp/init_postgres.sh

# lindfs mkdir /tmp
mkdir /home/lind/lind_project/src/safeposix-rust/tmp/tmp/

########################################## Bash ##########################################

echo -e "Loading bash and coreutils to RawPOSIX"

cd /home/lind/lind_project/tests/applications/bash/
echo "Bash starting coping..."

cp -r /home/lind/lind_project/tests/applications/bash/bash /home/lind/lind_project/src/safeposix-rust/tmp/bin/bash
cp -r /home/lind/lind_project/tests/applications/bash/bash /home/lind/lind_project/src/safeposix-rust/tmp/bin/sh

echo "Bash has been installed. Usage: lind /bin/bash /script.sh"

########################################## Coreutils ##########################################

echo "Coreutils starting..."

cd /home/lind/lind_project/tests/applications/coreutils/src;
find . -perm /a+x -type f -exec sh -c 'cp -r /home/lind/lind_project/tests/applications/coreutils/src/"$(basename {})" /home/lind/lind_project/src/safeposix-rust/tmp/bin/"$(basename {})"' \;

echo "Coreutils has been installed. Usage: lind /bin/(anycoretuil)"

########################################## Confs ##########################################

cp /etc/hosts /home/lind/lind_project/hosts
sed -i '/ip6/d' /home/lind/lind_project/hosts # remove inet6 addresses
echo -e "127.0.0.1\tLind" >> /home/lind/lind_project/hosts
sudo cp /home/lind/lind_project/hosts /home/lind/lind_project/src/safeposix-rust/tmp/etc/hosts
rm /home/lind/lind_project/hosts

echo "confs starting..."

sudo cp /etc/resolv.conf /home/lind/lind_project/src/safeposix-rust/tmp/etc/resolv.conf
sudo cp /etc/nsswitch.conf /home/lind/lind_project/src/safeposix-rust/tmp/etc/nsswitch.conf
sudo cp /etc/host.conf /home/lind/lind_project/src/safeposix-rust/tmp/etc/host.conf
sudo cp /usr/share/zoneinfo/America/New_York /home/lind/lind_project/src/safeposix-rust/tmp/etc/localtime 

sudo cp /home/lind/lind_project/src/scripts/includes/passwd /home/lind/lind_project/src/safeposix-rust/tmp/etc/passwd

########################################## dev file ##########################################

echo -e "mknod device files"

mkdir /home/lind/lind_project/src/safeposix-rust/tmp/dev
sudo mknod /home/lind/lind_project/src/safeposix-rust/tmp/dev/tty c 5 0
sudo chmod 666 /home/lind/lind_project/src/safeposix-rust/tmp/dev/tty
sudo mknod /home/lind/lind_project/src/safeposix-rust/tmp/dev/zero c 1 5
sudo chmod 666 /home/lind/lind_project/src/safeposix-rust/tmp/dev/zero
sudo mknod /home/lind/lind_project/src/safeposix-rust/tmp/dev/random c 1 8
sudo chmod 666 /home/lind/lind_project/src/safeposix-rust/tmp/dev/random
sudo mknod /home/lind/lind_project/src/safeposix-rust/tmp/dev/null c 1 3
sudo chmod 666 /home/lind/lind_project/src/safeposix-rust/tmp/dev/null
sudo mknod /home/lind/lind_project/src/safeposix-rust/tmp/dev/urandom c 1 9
sudo chmod 666 /home/lind/lind_project/src/safeposix-rust/tmp/dev/urandom

mv /home/lind/lind_project/src/safeposix-rust/tmp/usr/local/lib/python2.7/lib-dynload/psycopg2/lib/* /home/lind/lind_project/src/safeposix-rust/tmp/usr/local/lib/python2.7/lib-dynload/psycopg2/

########################################## Runtime scripts ##########################################

cp /home/lind/lind_project/tests/lamp_stack/pgbench/scripts/run_lind.sh /home/lind/lind_project/src/safeposix-rust/tmp/run_lind.sh
cp /home/lind/lind_project/tests/lamp_stack/pgbench/scripts/run_pgbench.sh /home/lind/lind_project/src/safeposix-rust/tmp/run_pgbench.sh
