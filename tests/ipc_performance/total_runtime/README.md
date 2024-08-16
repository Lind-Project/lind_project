# Read-Write total runtime

The purpose of the test is to find out the total time taken for write and read. This test runs 2 processes a write program piped to a read program. Each program write and read can be configured to run with a particular buffer size, the write program writes data to the pipe and read program reads data from the pipe. The benchmark runs the read and write programs with varying buffer sizes from 4 to 16 and compares the times in lind, native and userspace.

## Instructions to run test

To run all 3 configurations - `X-X`, `16-X`, `X-16` of the read-write buffer sizes
```sh
./run_pipe_performance.sh <count> <platform>
```

Or run each configuration individually
```sh
# Varying write and read buffers"
python3 gen_pipedata.py -w x -r x -c <number_of_runs>

#\nVarying write buffers"
python3 gen_pipedata.py -w x -r 16 -c <number_of_runs>

echo -e "\nVarying read buffers"
python3 gen_pipedata.py -w 16 -r x -c <number_of_runs>
```

## Instructions to plot graphs

```sh
./plot_runtimes.sh
```

It generates the bar charts for all the 3 configurations - `X-X`, `16-X`, `X-16`.