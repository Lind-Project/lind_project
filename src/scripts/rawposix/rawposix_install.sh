#!/bin/bash
# Replace RustPOSIX by RawPOSIX
rm -rf /home/lind/lind_project/src/safeposix-rust
cd /home/lind/lind_project/src/
git clone https://github.com/Lind-Project/RawPOSIX.git
mv /home/lind/lind_project/src/RawPOSIX /home/lind/lind_project/src/safeposix-rust

# Replace Makefile by new one
cp /home/lind/lind_projec/lind_project/src/scripts/rawposix/rawposix_mklind.sh /home/lind/lind_project/src/mklind

/home/lind/lind_project/src/mklind rustposix
/home/lind/lind_project/src/mklind install

