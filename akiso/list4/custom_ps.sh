#!/bin/bash

processes=($(ls /proc | grep "[0-9]"))
first_iteration=true

for pid in ${processes[@]}; do
    if [ $first_iteration = true ]; then
        echo "PPID PID COMM STATE TTY RSS PGID SID OPEN_FILES"
        first_iteration=false
    fi

    if [ -d "/proc/$pid" ]; then
        ppid=$(cat /proc/$pid/status | grep -E "^PPid" | awk '{ print $2 }')
        comm=$(cat /proc/$pid/status | grep -E "^Name" | awk '{ print $2 }')
        state=$(cat /proc/$pid/status | grep -E "^State" | awk '{ print $2 }')
        tty=$(readlink /proc/$pid/fd/0)
        rss=$(cat /proc/$pid/status | grep -E "^VmRSS" | awk '{ print $2 }')
        pgid=$(cat /proc/$pid/status | grep -E "^NSpgid" | awk '{ print $2 }')
        sid=$(cat /proc/$pid/status | grep -E "^NSsid" | awk '{ print $2 }')
        open_files=$(ls -l /proc/$pid/fd | awk 'NR > 1 { print $11 }' | sort | uniq | wc -l)

        echo "$ppid $pid $comm $state $tty $rss $pgid $sid $open_files"
    fi
done | column -t
