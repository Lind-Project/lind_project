# LAMP stack benchmark

The purpose of the test is to run performance benchmarks on the LAMP stack comprising of Postgres, Nginx, Flask and gunicorn. The test suite compiles and loads the entire LAMP stack into lindfs and then we can run different scripts to run specific benchmarks tests on the LAMP stack.

## Instructions to run test

```sh
# compile LAMP stack for lind (need not run always)
./compile.sh
```

Open 2 terminal sessions on the machine
```sh
# 1st terminal
# to setup and run the LAMP stack in lind
./lind_setup.sh
lind /bin/bash run_lamp.sh

# 2nd terminal
# run the wrk benchmark
wrk -t1 -c1 -d30 --timeout 30 http://localhost:80
```

To benchmark Postgres using a Python client connection (without Flask and Nginx)
```sh
./lind_setup_no_flask.sh
lind /bin/bash run_lamp_no_flask.sh
```

To benchmark Flask application served using an Nginx server (without Postgres)
```sh
./lind_setup_no_pg.sh
lind /bin/bash run_lamp_no_pg.sh
```

To benchmark Nginx serving a static output HTML (without Flask and Postgres)
```sh
./lind_setup_nginx_only.sh -s static_html_file_size_in_mbs
lind /bin/bash run_lamp_nginx_only.sh
```
