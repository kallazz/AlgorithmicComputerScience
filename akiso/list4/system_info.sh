#!/bin/bash

function display_time {
    local seconds=$1

    local days=$(($seconds/60/60/24))
    local hours=$(($seconds/60/60%24))
    local minutes=$(($seconds/60%60))
    local seconds_left=$(($seconds%60))

    printf "Days: %d Hours: %d Minutes: %d Seconds: %d\n" $days $hours $minutes $seconds_left
}

function convert_bytes {
    local bytes=$1

    local kilobytes=$(($bytes / 1024))
    local megabytes=$(($kilobytes / 1024))

    if (( $megabytes > 0 )); then
        printf "%dMB" $megabytes
    elif (( $kilobytes > 0 )); then
        printf "%dKB" $kilobytes
    else
        printf "%dB" $bytes
    fi
}

seconds=0
while true; do
    # Network speed
    bytes_received=$(cat /proc/net/dev | grep eth0 | awk '{ print $2 }')
    bytes_transmitted=$(cat /proc/net/dev | grep eth0 | awk '{ print $10 }')

    sleep 1
    seconds=$(($seconds + 1))

    bytes_received_2=$(cat /proc/net/dev | grep eth0 | awk '{ print $2 }')
    bytes_transmitted_2=$(cat /proc/net/dev | grep eth0 | awk '{ print $10 }')

    received_speed=$(($bytes_received_2 - $bytes_received))
    transmitted_speed=$(($bytes_transmitted_2 - $bytes_transmitted))

    received_speed_sum=$(($received_speed_sum + $received_speed))
    transmitted_speed_sum=$(($transmitted_speed_sum + $transmitted_speed))
    received_speed_mean=$(convert_bytes $(($received_speed_sum / $seconds)))
    transmitted_speed_mean=$(convert_bytes $(($transmitted_speed_sum / $seconds)))

    clear
    echo "*************************************** SYSTEM INFO ***************************************"
    echo "Network speed:"
    printf "Received speed: %s/s Transmitted speed: %s/s\n" $(convert_bytes $received_speed) $(convert_bytes $transmitted_speed)
    printf "Received speed mean: %s/s Transmitted speed mean: %s/s\n" $received_speed_mean $transmitted_speed_mean

    # Uptime
    uptime_in_seconds=$(cat /proc/uptime | awk -F '.' '{ print $1 }') # no fractional part
    echo "*******************************************************************************************"
    echo "Uptime:"
    display_time $uptime_in_seconds

    # Load average
    echo "*******************************************************************************************"
    printf "Load average in the last minute: %f\n" $(cat /proc/loadavg | awk '{ print $1 }')

    echo "*******************************************************************************************"

done
