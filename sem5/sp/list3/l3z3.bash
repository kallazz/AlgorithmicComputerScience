#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo -n "Usage: ./l3z2.bash <revision_number> <repo_url>"
    exit 1
fi

REVISION=$1
REPO_URL=$2
TEMP_DIR=$(mktemp -d)

trap "rm -rf $TEMP_DIR" EXIT

svn checkout -r "$REVISION" "$REPO_URL" "$TEMP_DIR" > /dev/null 2>&1

files=$(find $TEMP_DIR -type f ! -path "*/.svn/*")
all_unique_words=""

for file in $files; do
    all_unique_words=$(echo $all_unique_words $(cat $file | tr -s " \n" | tr " " "\n" | sort -u))
done

echo $all_unique_words | tr " " "\n" | sort | uniq -c

