#!/bin/bash
# Builds postgres and copies the library in lindfs.
echo "Compiling Postgres"
cd /home/lind/lind_project/tests/applications/postgres/
./bootstrap_nacl;
echo "Copying Postgres"
lindfs cp /home/lind/lind_project/tests/applications/postgres/src/interfaces/libpq/libpq.so.5.13 /lib/glibc/libpq.so.5
