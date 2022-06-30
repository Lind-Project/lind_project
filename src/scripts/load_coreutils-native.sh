#!/bin/bash
# Builds and loads coreutils executables into lind.
cd /home/lind/lind_project/tests/applications/coreutils;
./configure --enable-shared;
cd src;
find . -perm /a+x -type f -exec cp /home/lind/lind_project/tests/applications/coreutils/src/{} /home/lind/lind_project/native-python/bin/{} \;
echo "Coreutils has been installed.
