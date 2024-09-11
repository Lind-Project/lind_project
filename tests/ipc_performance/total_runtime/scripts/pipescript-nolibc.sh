#!/bin/bash

./writepipe-nolibc $1 | ./readpipe-nolibc $2
