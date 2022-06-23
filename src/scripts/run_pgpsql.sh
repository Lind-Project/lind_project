#!/bin/bash
# -F flag turns off fsync
/usr/local/pgsql/bin/postgres -F -d 5 -c listen_addresses='' -D /usr/local/pgsql/data/