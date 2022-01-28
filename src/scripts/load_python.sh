echo "Building python"
cd /home/lind/lind_project/tests/applications/python/;
./bootstrap_nacl || true;
lindfs cp /home/lind/lind_project/tests/applications/python/python /python;

echo "Copying libraries and configs"
lindfs cp /home/lind/lind_project/tests/applications/python/Lib /usr/local/lib/python2.7	
lindfs cp /usr/lib/python2.7/config/ /usr/lib/python2.7/config/
lindfs cp /usr/include/python2.7/ /usr/include/python2.7/
lindfs cp /home/lind/lind_project/src/scripts/includes/passwd /etc/passwd

echo "Python installed! To test it, load bash and use test_python.sh."