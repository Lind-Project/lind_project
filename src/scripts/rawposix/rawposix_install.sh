#!/bin/bash
# Replace RustPOSIX by RawPOSIX
rm -rf /home/lind/lind_project/src/safeposix-rust
cd /home/lind/lind_project/src/
git clone https://github.com/JustinCappos/rawposix.git
mv /home/lind/lind_project/src/rawposix /home/lind/lind_project/src/safeposix-rust
cd safeposix-rust
git checkout alice

/home/lind/lind_project/src/scripts/rawposix/rawposix_mklind.sh rustposix
/home/lind/lind_project/src/scripts/rawposix/rawposix_mklind.sh install

