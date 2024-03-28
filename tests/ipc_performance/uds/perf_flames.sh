#! /bin/bash

perf record -F 99 -a --call-graph dwarf -- ./scripts/uds 4 32
perf script | ../../../../FlameGraph/stackcollapse-perf.pl > out.perf-folded
../../../../FlameGraph/flamegraph.pl out.perf-folded > data/native-4-32GB.svg

perf record -F 99 -a --call-graph dwarf -- ./scripts/uds 8 32
perf script | ../../../../FlameGraph/stackcollapse-perf.pl > out.perf-folded
../../../../FlameGraph/flamegraph.pl out.perf-folded > data/native-8-32GB.svg

perf record -F 99 -a --call-graph dwarf -- ./scripts/uds 16 32
perf script | ../../../../FlameGraph/stackcollapse-perf.pl > out.perf-folded
../../../../FlameGraph/flamegraph.pl out.perf-folded > data/native-16-32GB.svg

perf record -F 99 -a --call-graph dwarf -- lind /uds 4 32
perf script | ../../../../FlameGraph/stackcollapse-perf.pl > out.perf-folded
../../../../FlameGraph/flamegraph.pl out.perf-folded > data/lind-4-32GB.svg

perf record -F 99 -a --call-graph dwarf -- lind /uds 8 32
perf script | ../../../../FlameGraph/stackcollapse-perf.pl > out.perf-folded
../../../../FlameGraph/flamegraph.pl out.perf-folded > data/lind-8-32GB.svg

perf record -F 99 -a --call-graph dwarf -- lind /uds 16 32
perf script | ../../../../FlameGraph/stackcollapse-perf.pl > out.perf-folded
../../../../FlameGraph/flamegraph.pl out.perf-folded > data/lind-16-32GB.svg
