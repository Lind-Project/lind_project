#!/bin/bash
python3 stats_collector.py data/sysbar_native_n_n data/sysbar_lind_n_n data/sysbar_n_n.json
python3 stats_collector.py data/sysbar_native_16_n data/sysbar_lind_16_n data/sysbar_16_n.json
python3 stats_collector.py data/sysbar_native_n_16 data/sysbar_lind_n_16 data/sysbar_n_16.json

python3 gen_syscall_plots.py data/sysbar_n_n.json N-N syscall-stacked-n-n.png
python3 gen_syscall_plots.py data/sysbar_16_n.json 16-N syscall-stacked-16-n.png
python3 gen_syscall_plots.py data/sysbar_n_16.json N-16 syscall-stacked-n-16.png

python3 gen_syscall_pie_plots.py data/sysbar_n_n.json N-N
python3 gen_syscall_pie_plots.py data/sysbar_16_n.json 16-N
python3 gen_syscall_pie_plots.py data/sysbar_n_16.json N-16
