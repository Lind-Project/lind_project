#!/bin/bash

if [ -f /etc/lsb-release ]; then
    . /etc/lsb-release
    if [ "$DISTRIB_ID" = "Ubuntu" ]; then
        export LIBRARY_PATH=/usr/lib/x86_64-linux-gnu
    fi
fi

echo "Compiling lind SFI test binaries"
x86_64-nacl-gcc scripts/write.c -o scripts/write.nexe -lrt -std=gnu99 -O3
x86_64-nacl-gcc scripts/close.c -o scripts/close.nexe -lrt -std=gnu99 -O3
x86_64-nacl-gcc scripts/getpid.c -o scripts/getpid.nexe -lrt -std=gnu99 -O3
lindfs cp /home/lind/lind_project/tests/ipc_performance/sfi_overhead/scripts/write.nexe /write.nexe
lindfs cp /home/lind/lind_project/tests/ipc_performance/sfi_overhead/scripts/close.nexe /close.nexe
lindfs cp /home/lind/lind_project/tests/ipc_performance/sfi_overhead/scripts/getpid.nexe /getpid.nexe

echo "Compiling native SFI test binaries"
/usr/local/gcc-4.4.3/bin/gcc scripts/write.c -o scripts/write -lrt -std=gnu99 -O3
/usr/local/gcc-4.4.3/bin/gcc scripts/close.c -o scripts/close -lrt -std=gnu99 -O3
/usr/local/gcc-4.4.3/bin/gcc scripts/getpid.c -o scripts/getpid -lrt -std=gnu99 -O3
