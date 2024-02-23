#!/bin/bash

cd /home/lind/lind_project/lind/lindenv/fs
rm *
/home/lind/lind_project/src/mklind install &> /dev/null

echo -e "Loading LAMP stack\n"
/home/lind/lind_project/src/scripts/lamp/load_lamp.sh > /dev/null
lindfs cp /home/lind/lind_project/tests/lamp_stack/profiling/run_lamp_nginx_only.sh /run_lamp_nginx_only.sh
lindfs cp /home/lind/lind_project/tests/lamp_stack/profiling/out.html /out.html

# echo -e "\nSetting up LAMP stack"
# lind /bin/bash run_lamp_nginx_only.sh
