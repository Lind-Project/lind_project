#!/bin/bash

python3 gen_runtimes_plots.py data/nat_x_x.json data/lind_x_x.json data/user_x_x.json N-N bar3-N-N.png
python3 gen_runtimes_plots.py data/nat_16_x.json data/lind_16_x.json data/user_16_x.json 16-N bar3-16-N.png
python3 gen_runtimes_plots.py data/nat_x_16.json data/lind_x_16.json data/user_x_16.json N-16 bar3-N-16.png
