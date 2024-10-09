#!/bin/bash

cd /home/lind/lind_project/lind/lindenv/fs
rm *
/home/lind/lind_project/src/mklind install &> /dev/null

echo -e "Loading LAMP stack\n"
/home/lind/lind_project/src/scripts/lamp/load_lamp.sh > /dev/null

echo -e "Loading static file\n"
/home/lind/lind_project/tests/lamp_stack/profiling/gen_static.sh

lindfs cp /home/lind/lind_project/tests/lamp_stack/profiling/lind_run_nginx.sh /lind_run_nginx.sh
