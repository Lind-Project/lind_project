/bin/cat test_content/content.txt | /bin/tr -d [:digit:] | /bin/grep -i "the" | /bin/uniq > test_content/cat_tr_grep_uniq.out
