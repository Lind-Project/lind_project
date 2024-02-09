#!/bin/bash

echo "Compiling native test binaries"
gcc scripts/poll_inet_tcp.c -o scripts/poll_inet_tcp -lpthread -std=gnu99 -O3 -lrt

echo "Compiling lind test binaries"
x86_64-nacl-gcc scripts/poll_inet_tcp.c -o scripts/poll_inet_tcp.nexe -lpthread -std=gnu99 -O3 -lrt
lindfs cp /home/lind/lind_project/tests/ipc_performance/inet/scripts/poll_inet_tcp.nexe /poll_inet_tcp
