#popen
gcc ../popen.c -o tempfolder/popen;
x86_64-nacl-gcc-4.4.3 ../popen.c -o tempfolder/popen.nexe -std=gnu99 -lpthread;
lindfs cp /home/lind/lind_project/tests/test_cases/coreutils_suite/tempfolder/popen.nexe tempfolder/popen

#pipescript
cd /home/lind/lind_project/tests/pipescript;
gcc write_1gb_var-test.c -o /home/lind/lind_project/tests/test_cases/coreutils_suite/tempfolder/write_to_pipe;
gcc read_from_pipe-test.c -o /home/lind/lind_project/tests/test_cases/coreutils_suite/tempfolder/read_from_pipe;

x86_64-nacl-gcc-4.4.3 write_1gb_var-test.c -o /home/lind/lind_project/tests/test_cases/coreutils_suite/tempfolder/write_to_pipe.nexe -std=gnu99 -lpthread;
x86_64-nacl-gcc-4.4.3 read_from_pipe-test.c -o /home/lind/lind_project/tests/test_cases/coreutils_suite/tempfolder/read_from_pipe.nexe -std=gnu99 -lpthread;

lindfs cp /home/lind/lind_project/tests/test_cases/coreutils_suite/tempfolder/write_to_pipe.nexe tempfolder/write_to_pipe
lindfs cp /home/lind/lind_project/tests/test_cases/coreutils_suite/tempfolder/read_from_pipe.nexe tempfolder/read_from_pipe
cd /home/lind/lind_project/tests/test_cases/coreutils_suite;