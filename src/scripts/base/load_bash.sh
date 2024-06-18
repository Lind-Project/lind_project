#!/bin/bash
# Builds and loads bash into lind.
cd /home/lind/lind_project/tests/applications/bash/

# lindfs cp /home/lind/lind_project/tests/applications/bash/bash /bin/bash
# lindfs cp /home/lind/lind_project/tests/applications/bash/bash /bin/sh

# Replaced by new lindfs
echo "Bash starting coping..."

mkdir -p /home/lind/lind_project/src/safeposix-rust/tmp/bin
cp -r /home/lind/lind_project/tests/applications/bash/bash /home/lind/lind_project/src/safeposix-rust/tmp/bin/bash
# mkdir /home/lind/lind_project/src/safeposix-rust/tmp/bin/sh
cp -r /home/lind/lind_project/tests/applications/bash/bash /home/lind/lind_project/src/safeposix-rust/tmp/bin/sh

echo "Bash has been installed. Usage: lind /bin/bash /script.sh"
