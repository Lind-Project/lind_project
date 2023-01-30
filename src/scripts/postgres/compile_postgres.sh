#!/bin/bash
# compiles postgres


echo "Compiling Postgres"
cd /home/lind/lind_project/tests/applications/postgres/
./bootstrap_nacl;

echo "Installing Postgres" # This script will be re-adjusted after postgres is fully usable.
make install DESTDIR=/home/lind/lind_project/lind/tmp
