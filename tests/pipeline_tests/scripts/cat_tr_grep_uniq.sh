/bin/cat test_content/content.txt | /bin/tr -d [:digit:] | /bin/grep -i "sherlock" | /bin/uniq > test_content/cat_tr_grep_uniq.out
