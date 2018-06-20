#!/bin/bash
###############################################################
### arch-wiki.sh search arch wiki from the cli
###
### Copyright (C) 2017 Dylan Schacht
###
### By: Dylan Schacht (deadhead)
### Email: deadhead3492@gmail.com
### Webpage: http://arch-anywhere.org
###
### Any questions, comments, or bug reports may be sent to above
### email address. Enjoy, and keep on using Arch.
###
### License: GPL v2.0
###############################################################

if [ "--help" == "$1" ] || [ "-h" == "$1" ]; then
	this=${0##*/}
	echo
	echo "Usage: $this archwiki page name"
	echo
	echo "  where archwiki page name is title of page on wiki.archlinux.org"
	echo
	echo "Examples:"
	echo "  $this ssh"
	echo "  $this installation guide"
	echo "  $this the arch way"
	echo
	exit 0
fi

if [ -n "$BROWSER" ]; then run_browser=$BROWSER
else BROWSER=lynx int=1
	until [ -n "$run_browser" ]
	 do
		if (which $BROWSER &>/dev/null); then run_browser=$BROWSER
		elif [ "$int" -eq "1" ]; then BROWSER=elinks
		elif [ "$int" -eq "2" ]; then BROWSER=links
		else
			echo "Please install one of the following packages to use this script: elinks links lynx"
			exit 1
		fi
		int=$((int+1))
	 done
fi

query="$*"  # get all params into single query string
query=${query// /_}  # substitute spaces with underscores in the query string

# load ArchWiki page with automatic redirect to the correct URL:
exec "$run_browser" "https://wiki.archlinux.org/index.php/Special:Search/${query}"
