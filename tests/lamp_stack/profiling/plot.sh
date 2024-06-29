#!/bin/bash

python3 gen_nginx_plots.py data/native_nginx.json data/lind_nginx.json data/rawposix_nginx.json nginx_bar.png
python3 gen_lamp_plots.py data/native_lamp.json data/lind_lamp.json data/rawposix_lamp.json lamp_bar.png
