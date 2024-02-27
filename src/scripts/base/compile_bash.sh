#!/bin/bash
# Builds and loads bash into lind.
cd /home/lind/lind_project/tests/applications/bash/
./bootstrap_nacl;

echo "Bash has been installed. Usage: lind /bin/bash /script.sh"
