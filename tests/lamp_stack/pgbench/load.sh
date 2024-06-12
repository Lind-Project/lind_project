#!/bin/bash

/home/lind/lind_project/src/scripts/base/load_confs.sh
/home/lind/lind_project/src/scripts/base/load_bash.sh
/home/lind/lind_project/src/scripts/base/load_coreutils.sh
/home/lind/lind_project/src/scripts/postgres/load_postgres.sh
# lindfs cp /home/lind/lind_project/tests/lamp_stack/pgbench/run_pg.sh run_pg.sh
# lindfs cp /home/lind/lind_project/tests/lamp_stack/pgbench/run_pgbench.sh run_pgbench.sh
# lindfs cp /home/lind/lind_project/tests/lamp_stack/pgbench/run_pgbench_2.sh run_pgbench_2.sh
cp /home/lind/lind_project/tests/lamp_stack/pgbench/run_pg.sh /home/lind/lind_project/src/safeposix-rust/tmp/run_pg.sh
cp /home/lind/lind_project/tests/lamp_stack/pgbench/run_pgbench.sh /home/lind/lind_project/src/safeposix-rust/tmp/run_pgbench.sh
cp /home/lind/lind_project/tests/lamp_stack/pgbench/run_pgbench_2.sh /home/lind/lind_project/src/safeposix-rust/tmp/run_pgbench_2.sh
