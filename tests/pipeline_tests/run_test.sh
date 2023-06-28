#!/bin/bash

echo "Test:" $(cat cat_test.sh)
time /bin/bash cat_test.sh
lind -t /bin/bash /pipeline_tests/cat_test.sh

printf "\n%80s\n" " " | tr ' ' '-' 

echo "Test:" $(cat cat_wc.sh)
time /bin/bash cat_wc.sh
lind -t /bin/bash /pipeline_tests/cat_wc.sh

printf "\n%80s\n" " " | tr ' ' '-' 

echo "Test:" $(cat grep_test.sh)
time /bin/bash grep_test.sh
lind -t /bin/bash /pipeline_tests/grep_test.sh

printf "\n%80s\n" " " | tr ' ' '-' 

echo "Test:" $(cat grep_wc.sh)
time /bin/bash grep_wc.sh
lind -t /bin/bash /pipeline_tests/grep_wc.sh

printf "\n%80s\n" " " | tr ' ' '-' 

echo "Test:" $(cat cat_grep.sh)
time /bin/bash cat_grep.sh
lind -t /bin/bash /pipeline_tests/cat_grep.sh

printf "\n%80s\n" " " | tr ' ' '-' 

echo "Test:" $(cat cat_grep_wc.sh)
time /bin/bash cat_grep_wc.sh
lind -t /bin/bash /pipeline_tests/cat_grep_wc.sh
