#!/bin/bash

sudo rm -rf /home/lind/lind_project/src/safeposix-rust
cd /home/lind/lind_project/src/
git clone https://github.com/Lind-Project/safeposix-rust.git
cd safeposix-rust
git checkout libc-write
export DEBUG_RUSTPOSIX=fast
/home/lind/lind_project/src/mklind rustposix
/home/lind/lind_project/src/mklind install
