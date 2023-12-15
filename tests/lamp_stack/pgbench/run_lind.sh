#!/bin/bash

echo -e "Resetting lind fs"
cd /home/lind/lind_project/lind/lindenv/fs
rm *
cd /home/lind/lind_project/tests/lamp_stack/pgbench

echo -e "Loading lind"
/home/lind/lind_project/src/mklind install &> /dev/null

echo -e "Loading postgres and bash"
./load.sh > /dev/null

echo -e "Initializing postgres"
lind /bin/bash init_postgres.sh > /dev/null

echo -e "Running pgbench"
lind /bin/bash run_pgbench.sh
