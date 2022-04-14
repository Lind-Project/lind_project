gcc ../popen.c -o tempfolder/popen;
x86_64-nacl-gcc-4.4.3 ../popen.c -o tempfolder/popen.nexe -std=gnu99 -lpthread;
lindfs cp /home/lind/lind_project/tests/test_cases/coreutils_suite/tempfolder/popen.nexe tempfolder/popen
