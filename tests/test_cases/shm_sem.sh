#!/bin/bash

gcc shmwrite1.c -o shmwrite1
gcc shmwrite2.c -o shmwrite2
./shmwrite1
./shmwrite2