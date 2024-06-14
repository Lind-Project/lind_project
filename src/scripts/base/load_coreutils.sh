#!/bin/bash
# Builds and loads coreutils executables into lind.
cd /home/lind/lind_project/tests/applications/coreutils/src;

# find . -perm /a+x -type f -exec lindfs cp /home/lind/lind_project/tests/applications/coreutils/src/{} /bin/{} \;
echo "Coreutils starting..."

# Replaced (AW)
# find . -perm /a+x -type f -exec cp -r /home/lind/lind_project/tests/applications/coreutils/src/{} /home/lind/lind_project/src/safeposix-rust/tmp/bin/{} \;
find . -perm /a+x -type f -exec sh -c 'cp -r /home/lind/lind_project/tests/applications/coreutils/src/"$(basename {})" /home/lind/lind_project/src/safeposix-rust/tmp/bin/"$(basename {})"' \;

echo "Coreutils has been installed. Usage: lind /bin/(anycoretuil)"
