#!/bin/bash
export LC_ALL=C
/usr/local/pgsql/bin/initdb --username=lind --debug --no-sync --auth=trust -E UNICODE --locale=C -D /usr/local/pgsql/data