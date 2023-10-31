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

echo -e "\nSetting up Flask\n"
./flask_setup.sh
cd $CWD
echo -e "\nFlask setup complete\n"
