/bin/grep -Eo '[+-]?[0-9]+([.][0-9]+)?' ./test_content/content.txt | /bin/uniq > grep_uniq.out
