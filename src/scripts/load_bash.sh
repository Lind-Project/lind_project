#!/bin/bash
# Builds and loads bash into lind.
cd /home/lind/lind_project/tests/applications/bash/
./bootstrap_nacl;
lindfs cp /home/lind/lind_project/tests/applications/bash/bash /bin/bash
echo "Bash has been installed. Usage: lind /bin/bash /script.sh"
