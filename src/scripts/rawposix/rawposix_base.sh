#!/bin/bash

# ------ dev files ------
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

# ------ bash ------
# Builds and loads bash into lind.
cd /home/lind/lind_project/tests/applications/bash/

# Replaced by new lindfs
echo "Bash starting coping..."

mkdir -p /home/lind/lind_project/src/safeposix-rust/tmp/bin
cp -r /home/lind/lind_project/tests/applications/bash/bash /home/lind/lind_project/src/safeposix-rust/tmp/bin/bash
cp -r /home/lind/lind_project/tests/applications/bash/bash /home/lind/lind_project/src/safeposix-rust/tmp/bin/sh

echo "Bash has been installed. Usage: lind /bin/bash /script.sh"

# ------ confs ------
mkdir -p /home/lind/lind_project/src/safeposix-rust/tmp/etc

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

# ------ coreutils ------
# Builds and loads coreutils executables into lind.
cd /home/lind/lind_project/tests/applications/coreutils/src;

echo "Coreutils starting..."

# Replaced
find . -perm /a+x -type f -exec sh -c 'cp -r /home/lind/lind_project/tests/applications/coreutils/src/"$(basename {})" /home/lind/lind_project/src/safeposix-rust/tmp/bin/"$(basename {})"' \;

echo "Coreutils has been installed. Usage: lind /bin/(anycoretuil)"
