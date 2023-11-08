#!/bin/bash

/bin/bash prep.sh 4096

echo -e "\nRunning pipeline tests on native"
python3 native_pipelines.py

echo -e "\nRunning pipeline tests on lind"
python3 lind_pipelines.py

echo -e "\nRemoving test output files"
rm test_content/*.out
rm test_content/content.txt
lindfs deltree /test_content/
