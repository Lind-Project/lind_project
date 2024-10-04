#!/bin/bash

mkdir -p data/
./compile.sh

echo -e "\n---------------- Pipe ----------------\n"
echo "Running on lind stack"
python3 gen_bufdata.py -c $1 -p "lind /pipe"

echo -e "\nRunning on native linux"
python3 gen_bufdata.py -c $1 -p "scripts/pipe"

echo -e "\n---------------- UDS ----------------\n"
echo "Running on lind stack"
python3 gen_bufdata.py -c $1 -p "lind /uds"

echo -e "\nRunning on native linux"
python3 gen_bufdata.py -c $1 -p "scripts/uds"

echo -e "\n---------------- Loop Back ----------------\n"
# Recompile RustPOSIX 
# rustup default nightly
# cd /home/lind/lind_project/src/
# rm -r safeposix-rust
# git clone https://github.com/Lind-Project/safeposix-rust.git
# cd safeposix-rust
# git checkout loopback_socket
# cd ../..
# src/mklind rustposix
# src/mklind install

cd /home/lind/lind_project/tests/ipc_performance/buf_allocate/
echo "Running on lind stack"
python3 gen_bufdata.py -c $1 -p "lind /loopback"

echo -e "\nRunning on native linux"
python3 gen_bufdata.py -c $1 -p "scripts/loopback"
