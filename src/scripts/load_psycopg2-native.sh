# Compiles postgres and psycopg2
# build python and postgres before running

mkdir -p /home/lind/lind_project/python-native/usr/local/lib/python2.7/lib-dynload/psycopg2/
cd /home/lind/lind_project/tests/applications/python-modules/psycopg2/
./build-native.sh

cp -r /home/lind/lind_project/tests/applications/python-modules/psycopg2/lib/* /home/lind/lind_project/fake_fs/usr/local/lib/python2.7/lib-dynload/psycopg2/
