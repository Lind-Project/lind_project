# Compiles postgres and psycopg2

./load_postgres.sh
cd /home/lind/lind_project/tests/applications/python-modules/psycopg2/
./bootstrap_nacl
lindfs cp /home/lind/lind_project/tests/applications/python-modules/psycopg2/lib/ /usr/local/lib/python2.7/lib-dynload/psycopg2/
