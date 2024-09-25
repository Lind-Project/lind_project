#!/bin/bash

echo -e "==== Running PGBENCH on Lind ===="

./compile_lind.sh

./load_lind.sh

scripts/run_lind.sh

