#!/bin/bash

python3 gen_vcs_plots.py data/nat_x_x.json data/lind_x_x.json data/user_x_x.json N-N vcs-N-N.png
python3 gen_vcs_plots.py data/nat_16_x.json data/lind_16_x.json data/user_16_x.json 16-N vcs-16-N.png
python3 gen_vcs_plots.py data/nat_x_16.json data/lind_x_16.json data/user_x_16.json N-16 vcs-N-16.png
