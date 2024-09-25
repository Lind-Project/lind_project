#!/bin/bash

echo -e "Resetting lind fs"
cd /home/lind/lind_project/lind/lindenv/fs
rm *
cd /home/lind/lind_project/tests/lamp_stack/pgbench

echo -e "Loading lind"
/home/lind/lind_project/src/mklind install &> /dev/null
