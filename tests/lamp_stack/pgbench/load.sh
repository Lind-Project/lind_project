#!/bin/bash

/home/lind/lind_project/src/scripts/base/load_confs.sh
/home/lind/lind_project/src/scripts/base/load_bash.sh
/home/lind/lind_project/src/scripts/base/load_coreutils.sh
/home/lind/lind_project/src/scripts/postgres/load_postgres.sh
lindfs cp /home/lind/lind_project/tests/lamp_stack/run_pgbench.sh run_pgbench.sh
