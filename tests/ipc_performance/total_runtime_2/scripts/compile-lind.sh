#!/bin/bash

x86_64-nacl-gcc scripts/pipe_write_read.c -o scripts/pipe.nexe -std=gnu99 -O3 -lrt -lpthread
lindfs cp /home/lind/lind_project/tests/ipc_performance/total_runtime_2/scripts/pipe.nexe /pipe