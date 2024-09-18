#!/bin/bash
# Replace RustPOSIX by RawPOSIX
rm -rf /home/lind/lind_project/src/safeposix-rust
cd /home/lind/lind_project/src/
git clone https://github.com/Lind-Project/RawPOSIX.git
mv /home/lind/lind_project/src/RawPOSIX /home/lind/lind_project/src/safeposix-rust

/home/lind/lind_projec/lind_project/src/scripts/rawposix/rawposix_mklind.sh rustposix
/home/lind/lind_projec/lind_project/src/scripts/rawposix/rawposix_mklind.sh install

