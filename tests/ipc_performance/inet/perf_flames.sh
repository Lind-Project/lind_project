#!/bin/bash

# perf record -F 99 -a --call-graph dwarf -- ./scripts/poll_inet_tcp
# perf script | ../../../../FlameGraph/stackcollapse-perf.pl > out.perf-folded
# ../../../../FlameGraph/flamegraph.pl out.perf-folded > data/native.svg

perf record -F 99 -a --call-graph dwarf -- lind /poll_inet_tcp
perf script | ../../../../FlameGraph/stackcollapse-perf.pl > out.perf-folded
../../../../FlameGraph/flamegraph.pl out.perf-folded > data/lind.svg
