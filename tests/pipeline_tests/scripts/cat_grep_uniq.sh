/bin/cat test_content/content.txt | /bin/grep -Eo '[+-]?[0-9]+([.][0-9]+)?' | /bin/uniq > test_content/cat_grep_uniq.out
