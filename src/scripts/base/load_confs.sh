#!/bin/bash

cp /etc/hosts /home/lind/lind_project/hosts
sed -i '/ip6/d' /home/lind/lind_project/hosts # remove inet6 addresses
echo -e "127.0.0.1\tLind" >> /home/lind/lind_project/hosts
# lindfs cp /home/lind/lind_project/hosts /etc/hosts # Adjusted as we also need Lind's ip as 127.0.0.1 in the list.
sudo cp /home/lind/lind_project/hosts /home/lind/lind_project/src/safeposix-rust/tmp/etc/hosts
rm /home/lind/lind_project/hosts

# lindfs cp /etc/resolv.conf /etc/resolv.conf
# lindfs cp /etc/nsswitch.conf /etc/nsswitch.conf
# lindfs cp /etc/host.conf /etc/host.conf
# lindfs cp /usr/share/zoneinfo/America/New_York /etc/localtime # As we don't have /etc/localtime default in lind.
sudo cp /etc/resolv.conf /home/lind/lind_project/src/safeposix-rust/tmp/etc/resolv.conf
sudo cp /etc/nsswitch.conf /home/lind/lind_project/src/safeposix-rust/tmp/etc/nsswitch.conf
sudo cp /etc/host.conf /home/lind/lind_project/src/safeposix-rust/tmp/etc/host.conf
sudo cp /usr/share/zoneinfo/America/New_York /home/lind/lind_project/src/safeposix-rust/tmp/etc/localtime 

# lindfs cp /home/lind/lind_project/src/scripts/includes/passwd /etc/passwd
sudo cp /home/lind/lind_project/src/scripts/includes/passwd /home/lind/lind_project/src/safeposix-rust/tmp/etc/passwd

