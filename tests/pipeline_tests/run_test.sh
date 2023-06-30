#!/bin/bash

echo "Test:" $(cat cat_test.sh)
time /bin/bash cat_test.sh
lind -t /bin/bash /pipeline_tests/cat_test.sh

printf "\n%80s\n" " " | tr ' ' '-' 

echo "Test:" $(cat grep_test.sh)
time /bin/bash grep_test.sh
lind -t /bin/bash /pipeline_tests/grep_test.sh

printf "\n%80s\n" " " | tr ' ' '-' 

echo "Test:" $(cat wc_test.sh)
time /bin/bash wc_test.sh
lind -t /bin/bash /pipeline_tests/wc_test.sh

# printf "\n%80s\n" " " | tr ' ' '-' 

# echo "Test:" $(cat sort_test.sh)
# time /bin/bash sort_test.sh
# lind -t /bin/bash /pipeline_tests/sort_test.sh

printf "\n%80s\n" " " | tr ' ' '-' 

echo "Test:" $(cat tr_test.sh)
time /bin/bash tr_test.sh
lind -t /bin/bash /pipeline_tests/tr_test.sh

printf "\n%80s\n" " " | tr ' ' '-' 

echo "Test:" $(cat uniq_test.sh)
time /bin/bash uniq_test.sh
lind -t /bin/bash /pipeline_tests/uniq_test.sh

printf "\n%80s\n" " " | tr ' ' '-' 

echo "Test:" $(cat cat_tr.sh)
time /bin/bash cat_tr.sh
lind -t /bin/bash /pipeline_tests/cat_tr.sh

printf "\n%80s\n" " " | tr ' ' '-' 

echo "Test:" $(cat cat_wc.sh)
time /bin/bash cat_wc.sh
lind -t /bin/bash /pipeline_tests/cat_wc.sh

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

# echo "Test:" $(cat grep_sort.sh)
# time /bin/bash grep_sort.sh
# lind -t /bin/bash /pipeline_tests/grep_sort.sh

# printf "\n%80s\n" " " | tr ' ' '-' 

# echo "Test:" $(cat cat_sort_uniq.sh)
# time /bin/bash cat_sort_uniq.sh
# lind -t /bin/bash /pipeline_tests/cat_sort_uniq.sh

# printf "\n%80s\n" " " | tr ' ' '-' 

# echo "Test:" $(cat grep_sort_uniq.sh)
# time /bin/bash grep_sort_uniq.sh
# lind -t /bin/bash /pipeline_tests/grep_sort_uniq.sh
