# Loads third party python modules at tests/applications/python-modules into Lind.
echo "Loading sitepackages..."
./load_sitepackages.sh

echo "Loading psycopg2..."
./load_psycopg2.sh
