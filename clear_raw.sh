rm -rf /home/lind/lind_project/src/safeposix-rust/tmp/

./src/mklind install

mkdir /home/lind/lind_project/src/safeposix-rust/tmp/dev
sudo mknod /home/lind/lind_project/src/safeposix-rust/tmp/dev/tty c 5 0
sudo chmod 666 /home/lind/lind_project/src/safeposix-rust/tmp/dev/tty
sudo mknod /home/lind/lind_project/src/safeposix-rust/tmp/dev/zero c 1 5
sudo chmod 666 /home/lind/lind_project/src/safeposix-rust/tmp/dev/zero
sudo mknod /home/lind/lind_project/src/safeposix-rust/tmp/dev/random c 1 8
sudo chmod 666 /home/lind/lind_project/src/safeposix-rust/tmp/dev/random
sudo mknod /home/lind/lind_project/src/safeposix-rust/tmp/dev/null c 1 3
sudo chmod 666 /home/lind/lind_project/src/safeposix-rust/tmp/dev/null
sudo mknod /home/lind/lind_project/src/safeposix-rust/tmp/dev/urandom c 1 9
sudo chmod 666 /home/lind/lind_project/src/safeposix-rust/tmp/dev/urandom

/home/lind/lind_project/src/scripts/lamp/load_lamp.sh
/home/lind/lind_project/tests/lamp_stack/profiling/flask_app/load.sh

mv /home/lind/lind_project/src/safeposix-rust/tmp/usr/local/lib/python2.7/lib-dynload/psycopg2/lib/* /home/lind/lind_project/src/safeposix-rust/tmp/usr/local/lib/python2.7/lib-dynload/psycopg2/
