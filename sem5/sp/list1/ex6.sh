#!/bin/bash

if [ "$#" -ne 1 ] || [ ! -d "$1" ]; then
    echo -n "Correct directory path was not provided."
    return 1
fi

for word in `find "$1" -type f -exec cat {} + | tr " " "\n" | tr -s "\n" "\n" | sort | uniq`
do
    grep_result="$(grep -rnE "\b$word\b.*\b$word\b*" -- "$1")"
    if [ ! -z "$grep_result" ]; then
        echo "$word:"
        echo "$grep_result"
    fi
done
