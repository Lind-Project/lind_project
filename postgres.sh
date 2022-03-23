#!/bin/bash

cd  /home/lind/lind_project/tests/applications/postgres/

/home/lind/lind_project/tests/applications/postgres/bootstrap_nacl

make install DESTDIR=/home/lind/lind_project/tmp

lindfs mkdir /usr

lindfs mkdir /usr/local

lindfs cp /home/lind/lind_project/tmp/usr/local/pgsql /usr/local/pgsql

#rm -rf /home/lind/lind_project/tmp #Optional
