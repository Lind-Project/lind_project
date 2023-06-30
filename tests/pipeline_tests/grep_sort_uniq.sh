/bin/grep -Eo '[+-]?[0-9]+([.][0-9]+)?' ./test_content/1GB.txt | /bin/sort -n | /bin/uniq > grep_sort_uniq.out
