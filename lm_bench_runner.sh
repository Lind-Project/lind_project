#!/bin/bash

lindfs cp /home/lind/lind_project/tests/applications/binutils-2.35.1_build/_install/usr /usr
lindfs cp /usr/lib/crti.o /usr/local/x86_64-linux/lib/crti.o
lindfs cp /usr/lib/crt1.o /usr/local/x86_64-linux/lib/crt1.o
lindfs cp /usr/lib/crtn.o /usr/local/x86_64-linux/lib/crtn.o
lindfs cp /usr/lib/ld-linux-x86-64.so.2 /usr/local/x86_64-linux/lib/ld-linux-x86-64.so.2
lindfs cp /usr/lib/libc.so /usr/local/x86_64-linux/lib/libc.so
lindfs cp /usr/lib/gcc/x86_64-pc-linux-gnu/13.2.1/crtend.o /usr/local/x86_64-linux/lib/crtend.o
lindfs cp /usr/lib/gcc/x86_64-pc-linux-gnu/13.2.1/crtbegin.o /usr/local/x86_64-linux/lib/crtbegin.o
lindfs cp /usr/include/ /usr/local/include/
lindfs cp /usr/lib/libc_nonshared.a /usr/lib/libc_nonshared.a
lindfs cp /usr/lib/gcc/x86_64-pc-linux-gnu/13.2.1/crtbegin.o /usr/local/x86_64-linux/lib/crtbegin.o
lindfs cp /home/lind/lind_project/src/safeposix-rust/libc.so.6 /usr/lib/libc.so.6
lindfs cp /home/lind/lind_project/src/safeposix-rust/ld-linux-x86-64.so.2 usr/lib/ld-linux-x86-64.so.2

lind /bw_pipe