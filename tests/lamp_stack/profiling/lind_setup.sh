#!/bin/bash

cd /home/lind/lind_project/lind/lindenv/fs
rm *
/home/lind/lind_project/src/mklind install &> /dev/null

echo -e "\nLoading LAMP stack\n"
/home/lind/lind_project/src/scripts/lamp/load_lamp.sh > /dev/null
/home/lind/lind_project/tests/lamp_stack/profiling/flask-app/load.sh > /dull/null

echo -e "\nInitializing Postgres\n"
lind /bin/bash init_postgres.sh

echo -e "\nSetting up LAMP stack\n"
lind /bin/bash run_lamp.sh &
