#!/bin/bash

rm -rf /home/lind/lind_project/src/safeposix-rust/tmp/

/home/lind/lind_project/src/scripts/rawposix/rawposix_mklind.sh install

/home/lind/lind_project/tests/lamp_stack/pgbench/load_rawposix.sh
