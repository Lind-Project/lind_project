/bin/grep -Eo '[+-]?[0-9]+([.][0-9]+)?' test_content/content.txt | /bin/uniq > test_content/grep_uniq.out
