# Read-Write syscall ratios

The purpose of the test is to find out the ratio of the time taken by different parts of the reads and writes - (`base_func`, `kernel_func`, `pipe_func`, `copy_func`). This test runs 2 processes a write program piped to a read program. Each program write and read can be configured to run with a particular buffer size, the write program writes data to the pipe and read program reads data from the pipe. The benchmark runs the read and write programs with varying buffer sizes from 4 to 16 and compares the times in lind and native.

## Instructions to run test

To run all 3 configurations - `N-N`, `16-N`, `N-16` of the read-write buffer sizes
```sh
./benchmark.sh <number_of_runs>
```

Or run each configuration individually
```sh
# varying read and write buffer sizes
./gen_sysbar_<platform>.sh a <number_of_runs>

# varying read buffer sizes
./gen_sysbar_<platform>.sh r <number_of_runs>

# varying write buffer sizes
./gen_sysbar_<platform>.sh w <number_of_runs>
```

## Instructions to plot graphs

```sh
./plot_syscall_ratios.sh
```

It generates the bar charts for all the 3 configurations - `N-N`, `16-N`, `N-16`.
