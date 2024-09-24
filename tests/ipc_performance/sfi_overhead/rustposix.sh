#!/bin/bash

cd /home/lind/lind_project/src/safeposix-rust
git checkout develop
export DEBUG_RUSTPOSIX
/home/lind/lind_project/src/mklind rustposix
/home/lind/lind_project/src/mklind install
