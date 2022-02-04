#!/bin/bash
#Builds everything needed to test psycopg2 in lind.

cd /home/lind/lind_project/src/scripts
./load_bash.sh
cd /home/lind/lind_project/src/scripts
./load_python.sh
cd /home/lind/lind_project/src/scripts
./load_python_libs.sh

echo "Building psycopg2"
cd /home/lind/lind_project/src/scripts
./load_psycopg2.sh
