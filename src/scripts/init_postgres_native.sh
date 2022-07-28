#!/bin/bash
export LC_ALL=C
/home/lind/lind_project/fake_fs/usr/local/pgsql/bin/initdb --username=lind --debug --no-sync --auth=trust -E UNICODE --locale=C -D /home/lind/lind_project/fake_fs/usr/local/pgsql/data
