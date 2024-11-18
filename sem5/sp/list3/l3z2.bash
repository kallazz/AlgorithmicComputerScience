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

cat $(find $TEMP_DIR -type f ! -path "*/.svn/*")| tr -s " \n" | tr " " "\n" | sort | uniq -c

