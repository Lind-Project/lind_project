#!/bin/bash
# Tests flask is running in lind.

cd /home/lind/lind_project/src/scripts
./load_bash.sh
cd /home/lind/lind_project/src/scripts
./load_python.sh
cd /home/lind/lind_project/src/scripts
./load_python_libs.sh

echo "Copying flask files:"
lindfs cp /home/lind/lind_project/tests/applications/python-modules/flask/ /usr/local/lib/python2.7/

echo "Copying script files:"
lindfs cp /home/lind/lind_project/src/scripts/includes/test_flask.py /hello.py
lindfs cp /home/lind/lind_project/src/scripts/includes/pythonscript.sh /pythonscript.sh
lind /bin/bash /pythonscript.sh
