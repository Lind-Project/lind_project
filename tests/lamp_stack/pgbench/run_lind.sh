#!/bin/bash

cd /home/lind/lind_project/lind/lindenv/fs
rm *

cd /home/lind/lind_project/
./src/mklind install &> /dev/null
./load.sh > /dev/null
lind /bin/bash init_postgres.sh 
lind /bin/bash pgbench.sh
