#!/bin/bash
gcc -Wall -fPIC -g -c add.c
gcc -Wall -fPIC -g -c sub.c

gcc -shared -o libmath.so add.o sub.o

gcc -g -c iso.c
gcc -o iso iso.o -L. -lmath
