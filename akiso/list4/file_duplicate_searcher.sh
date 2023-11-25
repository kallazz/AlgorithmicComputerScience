#!/bin/bash

if (( $# != 1 )); then
    echo "1 argument is required";
    exit 1
fi

dir=$1

if [ ! -d "$dir" ]; then
    echo "Directory doesn't exist";
    exit 1
fi

files=()
file_sizes=()
declare -A same_files
index=0
shopt -s globstar
for file in "$dir"/**; do
    if [ -f "$file" ]; then
        files+=("$file")
        size=$(stat -c %s "$file")
        file_sizes+=("$size")

        hash=$(sha1sum "$file" | awk '{ print $1 }')
        if [ -z  "${same_files[$hash]}" ]; then
            same_files[$hash]="$index"
        else
            same_files[$hash]="${same_files[$hash]} $index"
        fi

        index=$(($index + 1))
    fi
done

for i in "${!same_files[@]}"; do
    value=${same_files[$i]}
    value_length=${#value}
    # check if there are at least 2 files there
    if (( value_length >= 3 )); then
        file_indices=($value)
        for file_idx in "${file_indices[@]}"; do
            printf "%s Size: %dB\n" "${files[$file_idx]}" "${file_sizes[$file_idx]}"
        done
    fi
done | sort -k3 -n -r | column -t
