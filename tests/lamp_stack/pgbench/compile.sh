#!/bin/bash

echo "Compiling lind test binaries"
x86_64-nacl-gcc fileset_test.c -o fileset_test.nexe -std=gnu99 -lpthread
lindfs cp /home/lind/lind_project/tests/lamp_stack/pgbench/fileset_test.nexe /fileset_test
lindfs deltree /usr/local/pgsql/data/base/pgsql_tmp/pgsql_tmp15.0.sharedfileset

x86_64-nacl-gcc sync_file_test.c -o sync_file_test.nexe -std=gnu99 -lpthread
lindfs cp /home/lind/lind_project/tests/lamp_stack/pgbench/sync_file_test.nexe /sync_file_test
