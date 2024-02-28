# Buffer Read-Write tests

These tests perform writes and reads between the file descriptor and character buffers. The test runs on pretty large files (GBs in size) and benchmarks the time taken in reads and writes.

## Instructions to run test

```sh
./benchmark.sh <number of runs> <total size of file in GBs>
```

Change the python script name in `benchmark.sh` to run different tests. Options to choose are as follows:

- `run_lind.py` and `run_native.py`: Benchmarks total time taken by the program
- `run_lind_rw.py` and `run_native_rw.py`: Benchmarks total time taken by the program and the time taken by reads and writes
- `run_lind_rw_call.py` and `run_native_rw_call.py`: Benchmarks time taken by each read and write system call
