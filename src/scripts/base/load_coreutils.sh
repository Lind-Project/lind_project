#!/bin/bash
# Builds and loads coreutils executables into lind.
cd /home/lind/lind_project/tests/applications/coreutils/src;
find . -perm /a+x -type f -exec lindfs cp /home/lind/lind_project/tests/applications/coreutils/src/{} /bin/{} \;
echo "Coreutils has been installed. Usage: lind /bin/(anycoretuil)"
