# Loads third party python modules at tests/applications/python-modules into Lind.

load_flask(){
    lindfs cp /home/lind/lind_project/tests/applications/python-modules/flask/ /usr/local/lib/python2.7/
}

echo "Loading flask..."
./load_flask.sh

echo "Loading psycopg2..."
./load_psycopg2.sh