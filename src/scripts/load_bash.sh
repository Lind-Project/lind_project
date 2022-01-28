cd /home/lind/lind_project/tests/applications/bash/
./bootstrap_nacl || true;
lindfs cp /home/lind/lind_project/tests/applications/bash/bash /bin/bash
echo "Bash has been installed. Usage: lind /bin/bash /script.sh"