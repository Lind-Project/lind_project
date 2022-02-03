./load_bash.sh
./load_python.sh
./load_pylibs.sh

#!/bin/bash
# Tests python is running in lind.
echo "Copying files:"
lindfs cp /home/lind/lind_project/src/scripts/includes/test_flask.py /hello.py
lindfs cp /home/lind/lind_project/src/scripts/includes/pythonscript.sh /pythonscript.sh
lind /bin/bash /pythonscript.sh
