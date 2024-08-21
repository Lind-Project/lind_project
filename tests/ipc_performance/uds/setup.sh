#!/bin/bash

echo "Compile bash and coreutils"

cd /home/lind/lind_project/tests/applications/bash/
./bootstrap_nacl;

cd /home/lind/lind_project/tests/applications/coreutils;
./bootstrap_nacl;

lindfs cp /home/lind/lind_project/tests/applications/bash/bash /bin/bash
lindfs cp /home/lind/lind_project/tests/applications/bash/bash /bin/sh

echo "Bash has been installed. Usage: lind /bin/bash /script.sh"

/home/lind/lind_project/src/scripts/base/load_confs.sh

cd /home/lind/lind_project/tests/applications/coreutils/src;
find . -perm /a+x -type f -exec lindfs cp /home/lind/lind_project/tests/applications/coreutils/src/{} /bin/{} \;

echo "Coreutils has been installed. Usage: lind /bin/(anycoretuil)"

echo "Compile GCC-4.4.3"

cd /home/lind/lind_project/tests/applications/gcc-4.4.3
chmod +x lind-script
/home/lind/lind_project/tests/applications/gcc-4.4.3/lind-script

echo "alias gcc-4='/usr/local/gcc-4.4.3/bin/gcc'" >> "$HOME/.bashrc"
source "$HOME/.bashrc"

cd /home/lind/lind_project/tests/ipc_performance/uds
