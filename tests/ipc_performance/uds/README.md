# Unix Domain Sockets

The purpose of the test is to compare the performance of unix domain sockets in lind and native linux. There are two types of tests `uds_send_recv.c` and `uds_test.c`; in the first one we have the child and parent processes exchanging data between each other i.e. both processes send and recv data via domain sockets whereas in the second one the data transfer is one-way i.e. the parent is sending data while the child is receiving that data.

## Instructions to run test

```sh
./benchmark.sh <number_of_runs> <total_size_in_GBs>
```

Or run each platform individually
```sh
python3 gen_<platform>uds.py -b <buffer_size> -c <number_of_runs> -t <total_size_in_GBs>
```

## Instructions to plot graphs

```sh
python3 gen_uds_plots.py data/nat_x.json data/lind_x.json data/uds.png
```
