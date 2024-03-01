#!/bin/bash

cd /home/lind/lind_project/lind/lindenv/fs
rm *
/home/lind/lind_project/src/mklind install &> /dev/null

echo -e "Loading LAMP stack\n"
/home/lind/lind_project/src/scripts/lamp/load_lamp.sh > /dev/null
/home/lind/lind_project/tests/lamp_stack/profiling/flask-app/load.sh > /dev/null

echo -e "\nSetting up LAMP stack"
lind /bin/bash run_lamp_no_pg.sh
