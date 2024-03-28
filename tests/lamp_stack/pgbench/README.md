# Postgres PGBench

The purpose of the test is to run the `pgbench` performance test on the Postgres database instance to benchmark the database on both lind and native linux. The test suite compiles and loads postgres into lindfs and then runs the pgbench binary which is part of postgres source code to performance the postgres benchmark tests on lind.

## Instructions to run test

```sh
# compile postgres for lind (need not run always)
./compile.sh

# to run the benchmark
./run_lind.sh
```

To run pgbench only
```sh
# on the first run
./run_pgbench.sh

# on consecutive runs
./run_pgbench_2.sh
```
