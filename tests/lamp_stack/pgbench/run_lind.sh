#!/bin/bash

echo -e "Resetting lind fs"
cd /home/lind/lind_project/lind/lindenv/fs
rm *
cd /home/lind/lind_project/tests/lamp_stack/pgbench

echo -e "Loading lind"
/home/lind/lind_project/src/mklind install &> /dev/null

echo -e "Loading postgres and bash"
/home/lind/lind_project/tests/lamp_stack/pgbench/load.sh > /dev/null

echo -e "Initializing postgres"
lind /bin/bash init_postgres.sh > /dev/null

echo -e "\nRunning pgbench"
lind /bin/bash run_pgbench.sh

echo -e "\nRunning pgbench"
lind /bin/bash run_pgbench.sh
