#!/bin/bash

./src/scripts/base/load_confs.sh
./src/scripts/base/load_bash.sh
./src/scripts/base/load_coreutils.sh
./src/scripts/postgres/load_postgres.sh
lindfs cp /home/lind/lind_project/pgbench.sh pgbench.sh
