#!/bin/bash

FILES=/home/lind/lind_project/tests/pipeline-tests/bash-pipelines/*

cd FlameGraph

for f in $FILES
do
  testname=`basename $f`
  echo "Processing $testname file..."

  perf record -F 99 -a -g -- lind -t /bin/bash bash-pipelines/$testname
  perf script | ./stackcollapse-perf.pl > out.perf-folded
  ./flamegraph.pl out.perf-folded > $testname.svg

  cp $testname.svg ../graphs/$testname.svg


done

cd ..

