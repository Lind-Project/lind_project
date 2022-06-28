#!/bin/bash

cp /etc/hosts /home/lind/lind_project/hosts
sed -i '/ip6/d' hostsi # remove inet6 addresses
echo -e "127.0.0.1\tLind" >> /home/lind/lind_project/hosts
lindfs cp /home/lind/lind_project/hosts /etc/hosts # Adjusted as we also need Lind's ip as 127.0.0.1 in the list.
rm /home/lind/lind_project/hosts

lindfs cp /etc/resolv.conf /etc/resolv.conf
lindfs cp /etc/nsswitch.conf /etc/nsswitch.conf
lindfs cp /etc/host.conf /etc/host.conf
lindfs cp /usr/share/zoneinfo/America/New_York /etc/localtime # As we don't have /etc/localtime default in lind.

lindfs cp /home/lind/lind_project/src/scripts/includes/passwd /etc/passwd

