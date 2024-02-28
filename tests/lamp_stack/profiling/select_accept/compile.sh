#!/bin/bash

echo "Compiling native test binaries"
gcc select_accept.c -o select_accept -std=gnu99 -lpthread
gcc select_accept_client.c -o select_accept_client -std=gnu99 -lpthread
gcc contention_test_server.c -o contention_test_server -std=gnu99 -lpthread
gcc polluted_select_server.c -o polluted_select_server -std=gnu99 -lpthread
gcc polluted_select_client.c -o polluted_select_client -std=gnu99 -lpthread

echo "Compiling lind test binaries"
x86_64-nacl-gcc select_accept.c -o select_accept.nexe -std=gnu99 -lpthread
x86_64-nacl-gcc select_accept_client.c -o select_accept_client.nexe -std=gnu99 -lpthread
x86_64-nacl-gcc contention_test_server.c -o contention_test_server.nexe -std=gnu99 -lpthread
x86_64-nacl-gcc polluted_select_server.c -o polluted_select_server.nexe -std=gnu99 -lpthread
x86_64-nacl-gcc polluted_select_client.c -o polluted_select_client.nexe -std=gnu99 -lpthread
lindfs cp /home/lind/lind_project/tests/lamp_stack/profiling/select_accept/select_accept.nexe /select_accept
lindfs cp /home/lind/lind_project/tests/lamp_stack/profiling/select_accept/select_accept_client.nexe /select_accept_client
lindfs cp /home/lind/lind_project/tests/lamp_stack/profiling/select_accept/contention_test_server.nexe /contention_test_server
lindfs cp /home/lind/lind_project/tests/lamp_stack/profiling/select_accept/run.sh /run.sh
lindfs cp /home/lind/lind_project/tests/lamp_stack/profiling/select_accept/polluted_select_server.nexe /polluted_select_server
lindfs cp /home/lind/lind_project/tests/lamp_stack/profiling/select_accept/polluted_select_client.sh /polluted_select_client.sh
