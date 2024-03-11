#!/bin/bash

echo "Compiling native test binaries"
gcc scripts/context.c -o scripts/context -O2 -lpthread -lrt
gcc scripts/context_pipe.c -o scripts/context_pipe -O2 -lpthread -lrt
gcc scripts/ds.c -o scripts/ds -O2 -lpthread -lrt
gcc scripts/func.c -o scripts/func -O2 -lpthread -lrt
gcc scripts/getpid.c -o scripts/getpid -O2 -lpthread -lrt
gcc scripts/memcpy.c -o scripts/memcpy -O2 -lpthread -lrt
gcc scripts/shm_proc.c -o scripts/shm_proc -O2 -lpthread -lrt
gcc scripts/shm.c -o scripts/shm -O2 -lpthread -lrt

echo "Compiling lind test binaries"
x86_64-nacl-gcc scripts/context.c -o scripts/context.nexe -O2 -std=gnu99 -lpthread -lrt
x86_64-nacl-gcc scripts/context_pipe.c -o scripts/context_pipe.nexe -O2 -std=gnu99 -lpthread -lrt
x86_64-nacl-gcc scripts/ds.c -o scripts/ds.nexe -O2 -std=gnu99 -lpthread -lrt
x86_64-nacl-gcc scripts/func.c -o scripts/func.nexe -O2 -std=gnu99 -lpthread -lrt
x86_64-nacl-gcc scripts/getpid.c -o scripts/getpid.nexe -O2 -std=gnu99 -lpthread -lrt
x86_64-nacl-gcc scripts/memcpy.c -o scripts/memcpy.nexe -O2 -std=gnu99 -lpthread -lrt
x86_64-nacl-gcc scripts/shm_proc.c -o scripts/shm_proc.nexe -O2 -std=gnu99 -lpthread -lrt
x86_64-nacl-gcc scripts/shm.c -o scripts/shm.nexe -O2 -std=gnu99 -lpthread -lrt

echo "Copying test cases to lindfs"
lindfs cp $PWD/scripts/context.nexe /context
lindfs cp $PWD/scripts/context_pipe.nexe /context_pipe
lindfs cp $PWD/scripts/ds.nexe /ds
lindfs cp $PWD/scripts/func.nexe /func
lindfs cp $PWD/scripts/getpid.nexe /getpid
lindfs cp $PWD/scripts/memcpy.nexe /memcpy
lindfs cp $PWD/scripts/shm_proc.nexe /shm_proc
lindfs cp $PWD/scripts/shm.nexe /shm
