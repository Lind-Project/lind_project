/bin/grep -Eo '[+-]?[0-9]+([.][0-9]+)?' test_content/content.txt | /bin/sort -n | /bin/uniq > test_content/grep_sort_uniq.out
