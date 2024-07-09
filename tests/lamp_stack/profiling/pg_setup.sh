#!/bin/bash

cd /home/lind/lind_project/tests/applications/postgres/

./configure
make
sudo make install
sudo mkdir -m 770 /usr/local/pgsql/data/
sudo chown lind:lind /usr/local/pgsql/data
# sudo mkdir -m 770 /home/lind/lind_project/src/safeposix-rust/tmp/usr/local/pgsql/data/
# sudo chown lind:lind /home/lind/lind_project/src/safeposix-rust/tmp/usr/local/pgsql/data

export LC_ALL=C
/usr/local/pgsql/bin/initdb --username=lind --debug --no-sync --auth=trust -E UNICODE --locale=C -D /usr/local/pgsql/data
