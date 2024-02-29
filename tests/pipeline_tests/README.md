# Unix bash pipelines

The purpose of the test is to compare the times of different unix bash pipeline combinations in both lind and native to benchmark the performance of unix pipes and the bash coreutils like `cat`, `grep`, `wc`, etc.

## Instructions to run test

```sh
./benchmark.sh <number_of_runs> <size_of_file_in_MBs>
```

To generate syscall ratios for I/O and pipe read-writes
```sh
# varying read and write buffer sizes
./gen_sysbar_<platform>.sh <tests.txt> <number_of_runs>
```

To run cat pipelines benchmark, each benchmark is N number of cats in a pipe
```sh
python3 cat_bench.py -c <number_of_runs>
```

## Instructions to plot graphs

```sh
python3 gen_pipelin_plots.py data/native_pipelines.json data/lind_pipelines.json data/pipelines.png
```

To generate plots for the cat pipelines benchmark
```sh
python3 cat_bench.py data/cat_native.json data/cat_lind.json data/cat_bench.png
```
