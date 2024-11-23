#!/bin/bash

if [ "$#" -ne 3 ]; then
  echo "Usage: $0 <r1> <r2> <SVN_URL>"
  exit 1
fi

svn_min_revision_number=$1
svn_max_revision_number=$2
svn_repository_url=$3

git_repository_directory=$(basename "$svn_repository_url")
temp_svn_repository_directory="temp_svn"

rm -rf "$git_repository_directory"
git init "$git_repository_directory" >/dev/null 2>&1

trap "rm -rf $temp_svn_repository_directory" EXIT

for ((revision_number = svn_min_revision_number; revision_number <= svn_max_revision_number; revision_number++)); do
      rm -rf "$temp_svn_repository_directory"
      mkdir "$temp_svn_repository_directory"
      svn export --force --revision "$revision_number" "$svn_repository_url" "$temp_svn_repository_directory" >/dev/null 2>&1
      find "$temp_svn_repository_directory" \( -name ".git" -o -name ".svn" -o -name ".gitignore" \) -exec rm -rf {} +

      cd "$git_repository_directory"
      find . -mindepth 1 -name ".git" -prune -o -exec rm -rf {} +
      cp -r ../"$temp_svn_repository_directory"/* .
      git add .
      
      svn_log=$(svn log --revision "$revision_number" "$svn_repository_url" | sed -n '/^$/,$p' | tail -n +2)
      git commit -m "$svn_log" >/dev/null 2>&1

      cd - >/dev/null 2>&1
done

