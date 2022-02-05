#!/bin/bash
#Builds everything needed to test Flask in lind.

cd /home/lind/lind_project/src/scripts
./load_bash.sh
cd /home/lind/lind_project/src/scripts
./load_python.sh
cd /home/lind/lind_project/src/scripts
./load_python_libs.sh
cd /home/lind/lind_project/src/scripts
./load_flask.sh
