#!/bin/bash

/home/lind/lind_project/src/scripts/base/load_confs.sh
/home/lind/lind_project/src/scripts/base/load_bash.sh
/home/lind/lind_project/src/scripts/base/load_coreutils.sh
/home/lind/lind_project/src/scripts/postgres/load_postgres.sh
lindfs cp /home/lind/lind_project/tests/lamp_stack/pgbench/run_pg.sh run_pg.sh
lindfs cp /home/lind/lind_project/tests/lamp_stack/pgbench/run_pgbench.sh run_pgbench.sh
lindfs cp /home/lind/lind_project/tests/lamp_stack/pgbench/run_pgbench2.sh run_pgbench2.sh
