# generate test content
echo "Generating test content..."
./gen_test_content.sh 1024 1GB.txt

# load test files
echo "Loading test files..."

lindfs mkdir /pipeline_tests/
lindfs cp /home/lind/lind_project/tests/pipeline_tests/cat_test.sh /pipeline_tests/cat_test.sh
lindfs cp /home/lind/lind_project/tests/pipeline_tests/cat_grep_wc.sh /pipeline_tests/cat_grep_wc.sh
lindfs cp /home/lind/lind_project/tests/pipeline_tests/cat_grep.sh /pipeline_tests/cat_grep.sh
lindfs cp /home/lind/lind_project/tests/pipeline_tests/cat_wc.sh /pipeline_tests/cat_wc.sh
lindfs cp /home/lind/lind_project/tests/pipeline_tests/grep_test.sh /pipeline_tests/grep_test.sh
lindfs cp /home/lind/lind_project/tests/pipeline_tests/grep_wc.sh /pipeline_tests/grep_wc.sh
lindfs cp /home/lind/lind_project/tests/pipeline_tests/grep_sort_uniq.sh /pipeline_tests/grep_sort_uniq.sh

# load test data
echo "Loading test data..."
lindfs cp /home/lind/lind_project/tests/pipeline_tests/test_content /test_content/
