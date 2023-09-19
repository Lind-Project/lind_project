#!/bin/bash

./tempfolder/shm_sem_server &
sleep 1
./tempfolder/shm_sem_client
