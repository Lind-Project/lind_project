# INET poll performance tests

This test compares the performance of poll syscalls in a INET TCP ping pong program. There is a pinger process in the child fork and a ponger process in the parent, both the processes perform ping pong using INET TCP sockets.

## Instructions to run test

```sh
./benchmark.sh <number of runs>
```

Change the `ROUNDS` constant value in `scripts/poll_inet_tcp.c` based on your requirements to increase or decrease the number of ping pong messages between the processes.
