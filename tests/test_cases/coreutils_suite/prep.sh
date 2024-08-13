
BASE_DIR=$LIND_NATIVE_HOME

#popen
gcc ../popen.c -o tempfolder/popen;
x86_64-nacl-gcc-4.4.3 ../popen.c -o tempfolder/popen.nexe -std=gnu99 -lpthread;
lindfs cp $BASE_DIR/tests/test_cases/coreutils_suite/tempfolder/popen.nexe tempfolder/popen

#pipescript
cd $BASE_DIR/tests/pipescript;
gcc write_1gb_var-test.c -o $BASE_DIR/tests/test_cases/coreutils_suite/tempfolder/write_to_pipe;
gcc read_from_pipe-test.c -o $BASE_DIR/tests/test_cases/coreutils_suite/tempfolder/read_from_pipe;

x86_64-nacl-gcc-4.4.3 write_1gb_var-test.c -o $BASE_DIR/tests/test_cases/coreutils_suite/tempfolder/write_to_pipe.nexe -std=gnu99 -lpthread;
x86_64-nacl-gcc-4.4.3 read_from_pipe-test.c -o $BASE_DIR/tests/test_cases/coreutils_suite/tempfolder/read_from_pipe.nexe -std=gnu99 -lpthread;

lindfs cp $BASE_DIR/tests/test_cases/coreutils_suite/tempfolder/write_to_pipe.nexe tempfolder/write_to_pipe
lindfs cp $BASE_DIR/tests/test_cases/coreutils_suite/tempfolder/read_from_pipe.nexe tempfolder/read_from_pipe

#shm
cd $BASE_DIR/tests/test_cases/coreutils_suite;
gcc shm_read.c -o $BASE_DIR/tests/test_cases/coreutils_suite/tempfolder/shm_read;
gcc shm_write.c -o $BASE_DIR/tests/test_cases/coreutils_suite/tempfolder/shm_write;

x86_64-nacl-gcc-4.4.3 shm_read.c -o $BASE_DIR/tests/test_cases/coreutils_suite/tempfolder/shm_read.nexe -std=gnu99 -lpthread;
x86_64-nacl-gcc-4.4.3 shm_write.c -o $BASE_DIR/tests/test_cases/coreutils_suite/tempfolder/shm_write.nexe -std=gnu99 -lpthread;

lindfs cp $BASE_DIR/tests/test_cases/coreutils_suite/tempfolder/shm_read.nexe tempfolder/shm_read
lindfs cp $BASE_DIR/tests/test_cases/coreutils_suite/tempfolder/shm_write.nexe tempfolder/shm_write

#shm_sem
gcc shm_sem_server.c -o $BASE_DIR/tests/test_cases/coreutils_suite/tempfolder/shm_sem_server -lpthread;
gcc shm_sem_client.c -o $BASE_DIR/tests/test_cases/coreutils_suite/tempfolder/shm_sem_client -lpthread;
gcc shm_sem_client_fork.c -o $BASE_DIR/tests/test_cases/coreutils_suite/tempfolder/shm_sem_client_fork -lpthread;

x86_64-nacl-gcc-4.4.3 shm_sem_server.c -o $BASE_DIR/tests/test_cases/coreutils_suite/tempfolder/shm_sem_server.nexe -std=gnu99 -lpthread;
x86_64-nacl-gcc-4.4.3 shm_sem_client.c -o $BASE_DIR/tests/test_cases/coreutils_suite/tempfolder/shm_sem_client.nexe -std=gnu99 -lpthread;
x86_64-nacl-gcc-4.4.3 shm_sem_client_fork.c -o $BASE_DIR/tests/test_cases/coreutils_suite/tempfolder/shm_sem_client_fork.nexe -std=gnu99 -lpthread;

lindfs cp $BASE_DIR/tests/test_cases/coreutils_suite/tempfolder/shm_sem_server.nexe tempfolder/shm_sem_server
lindfs cp $BASE_DIR/tests/test_cases/coreutils_suite/tempfolder/shm_sem_client.nexe tempfolder/shm_sem_client
lindfs cp $BASE_DIR/tests/test_cases/coreutils_suite/tempfolder/shm_sem_client_fork.nexe tempfolder/shm_sem_client_fork

cd $BASE_DIR/tests/test_cases/coreutils_suite;
