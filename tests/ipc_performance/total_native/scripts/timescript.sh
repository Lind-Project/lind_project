#!/bin/bash

TIMEFORMAT=%R

for i in $(seq 1 50);
do
	time /bin/bash ps32var2.sh 16 16
done
