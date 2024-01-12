#!/bin/bash

/usr/local/pgsql/bin/postgres -F -c listen_addresses='' -D /usr/local/pgsql/data/
