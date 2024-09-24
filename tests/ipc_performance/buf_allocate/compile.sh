#!/bin/bash

x86_64-nacl-gcc scripts/pipe.c -o scripts/pipe.nexe -lrt -std=gnu99 -O3
x86_64-nacl-gcc scripts/uds.c -o scripts/uds.nexe -lrt -std=gnu99 -O3
lindfs cp /home/lind/lind_project/tests/ipc_performance/buf_allocate/scripts/uds.nexe /uds
lindfs cp /home/lind/lind_project/tests/ipc_performance/buf_allocate/scripts/pipe.nexe /pipe

/usr/local/gcc-4.4.3/bin/gcc scripts/pipe.c -o scripts/pipe -lrt -std=gnu99 -O3
/usr/local/gcc-4.4.3/bin/gcc scripts/uds.c -o scripts/uds -lrt -std=gnu99 -O3