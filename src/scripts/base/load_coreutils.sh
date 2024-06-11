#!/bin/bash
# Builds and loads coreutils executables into lind.
cd /home/lind/lind_project/tests/applications/coreutils/src;

find . -perm /a+x -type f -exec lindfs cp /home/lind/lind_project/tests/applications/coreutils/src/{} /bin/{} \;

# Replaced (AW)
find . -perm /a+x -type f -exec cp -r /home/lind/lind_project/tests/applications/coreutils/src/{} /home/lind/lind_project/src/safeposix-rust/tmp/bin/{} \;

echo "Coreutils has been installed. Usage: lind /bin/(anycoretuil)"
