#!/bin/bash

echo -e "Loading postgres to Lind"
/home/lind/lind_project/src/scripts/postgres/load_postgres.sh

echo -e "Loading bash and coreutils to Lind"
/home/lind/lind_project/src/scripts/base/load_confs.sh
/home/lind/lind_project/src/scripts/base/load_bash.sh
/home/lind/lind_project/src/scripts/base/load_coreutils.sh

lindfs cp /home/lind/lind_project/tests/lamp_stack/pgbench/scripts/run_lind.sh run_lind.sh
lindfs cp /home/lind/lind_project/tests/lamp_stack/pgbench/run_pgbench.sh run_pgbench.sh
