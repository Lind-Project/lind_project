#!/bin/bash

CWD="$PWD"
echo -e "\nSetting up postgres\n"
./pg_setup.sh
cd $CWD
echo -e "\nPostgres setup complete\n"

echo -e "\nSetting up NGINX\n"
./nginx_setup.sh
cd $CWD
echo -e "\nNGINX setup complete\n"

# echo -e "\nStarting LAMP\n"
# ./run_lamp_native.sh
/home/lind/lind_project/tests/lamp_stack/profiling/gen_static.sh
echo -e "\nNGINX static file loading complete\n"
