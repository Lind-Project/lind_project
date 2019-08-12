#!/bin/bash
# Given a repy file with preprocessor directives, check they are all valid

# get basename and dirname
file_name="${1##*/}"
file_path="${1%%$file_name}"

# handle no directory parts in pathname and strip trailing '/'
if [[ -z "$file_path" ]]; then
	file_path="."
else
	file_path="${file_path##/}"
fi

# build path set
paths+=("$file_path/")
paths+=("$file_path/fs/")
paths+=("$file_path/net/")
paths+=("$file_path/sys/")
paths+=("$file_path/lind/")
paths+=("$file_path/xmplrpc/")
paths+=("$file_path/librepy/")

# build the list of files to include
mapfile -t files < <(awk '/^include/{print $2}' "$1")

# map includes over path set and abort if not found in any of the paths
for file in "${files[@]}"; do
	if [[ -z "$(find "${paths[@]}" -type f -name "$file" 2>/dev/null)" ]]; then
		printf 'Error: include %s is missing in %s.\n' "$file" "$file_name" >&2
		exit 1
	fi
done
