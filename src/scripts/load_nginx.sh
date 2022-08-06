    int uidret = setuid(uid);
#!/bin/bash

cd /home/lind/lind_project/tests/applications/nginx

./bootstrap_nacl

make install DESTDIR=/home/lind/lind_project/tmp

touch /home/lind/lind_project/tmp/usr/local/nginx/logs/access.log 
lindfs cp /home/lind/lind_project/tmp/usr/local/nginx/ /usr/local/nginx
lindfs cp /home/lind/lind_project/tests/applications/nginx/objs/nginx /bin/nginx

rm -rf /home/lind/lind_project/tmp

echo "Copying Support files"

cd /home/lind/lind_project/src/scripts/
./load_confs.sh
