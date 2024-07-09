rm -rf /home/lind/lind_project/src/safeposix-rust/tmp/

./src/mklind install

/home/lind/lind_project/src/scripts/lamp/load_lamp.sh
/home/lind/lind_project/tests/lamp_stack/profiling/flask_app/load.sh

mv /home/lind/lind_project/src/safeposix-rust/tmp/usr/local/lib/python2.7/lib-dynload/psycopg2/lib/* /home/lind/lind_project/src/safeposix-rust/tmp/usr/local/lib/python2.7/lib-dynload/psycopg2/
