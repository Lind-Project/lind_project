#!/bin/bash
# Tests psycopg2 is running in lind.

cd /home/lind/lind_project/src/scripts
./load_bash.sh
cd /home/lind/lind_project/src/scripts
./load_python.sh
cd /home/lind/lind_project/src/scripts
./load_python_libs.sh

echo "Building psycopg2"
cd /home/lind/lind_project/src/scripts
./load_psycopg2

lindfs cp /home/lind/lind_project/src/scripts/includes/test_psycopg2.py /hello.py
lindfs cp /home/lind/lind_project/src/scripts/includes/pythonscript.sh /pythonscript.sh
lind /bin/bash /pythonscript.sh
