#!/bin/bash

# generate test content
echo "Generating test content..."
./gen_test_content.sh $1 content.txt

# load test files
echo "Loading test files..."

lindfs mkdir /pipeline_tests/
lindfs cp /home/lind/lind_project/tests/pipeline_tests/scripts/ /pipeline_tests/

# load test data
echo "Loading test data..."
lindfs cp /home/lind/lind_project/tests/pipeline_tests/test_content /test_content/
