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

received_speed_sum=0
transmitted_speed_sum=0
last_bytes_received=$(cat /proc/net/dev | grep eth0 | awk '{ print $2 }')
last_bytes_transmitted=$(cat /proc/net/dev | grep eth0 | awk '{ print $10 }')

cpu_count=$(cat /proc/stat | grep -E "cpu[0-9]+" | wc -l)
cpu_names=($(cat /proc/stat | grep -E "cpu[0-9]+" | awk '{ print $1 }'))
cpu_last_sums=()
cpu_last_idles=()

for ((i = 0; i < $cpu_count; i++)); do
    cpu_last_sums+=(0)
    cpu_last_idles+=(0)
done

seconds=0

while true; do
    clear
    echo "--------------------------------------- SYSTEM INFO ---------------------------------------"
    seconds=$(($seconds + 1))

    # Network speed
    bytes_received=$(cat /proc/net/dev | grep eth0 | awk '{ print $2 }')
    bytes_transmitted=$(cat /proc/net/dev | grep eth0 | awk '{ print $10 }')

    received_speed=$(($bytes_received - $last_bytes_received))
    transmitted_speed=$(($bytes_transmitted - $last_bytes_transmitted))

    received_speed_sum=$(($received_speed_sum + $received_speed))
    transmitted_speed_sum=$(($transmitted_speed_sum + $transmitted_speed))
    received_speed_mean=$(convert_bytes $(($received_speed_sum / $seconds)))
    transmitted_speed_mean=$(convert_bytes $(($transmitted_speed_sum / $seconds)))

    echo "Network speed:"
    printf "Received speed: %s/s Transmitted speed: %s/s\n" $(convert_bytes $received_speed) $(convert_bytes $transmitted_speed)
    printf "Received speed mean: %s/s Transmitted speed mean: %s/s\n" $received_speed_mean $transmitted_speed_mean

    printf "Graphical representation:\n"
    printf "Received:    "
    for ((i = 0; i < $((received_speed / 10)); i++)); do
        if (( $i == 45 )); then
            # max number of squares
            break
        fi
        printf "▇"
    done
    printf "\n"

    printf "Transmitted: "
    for ((i = 0; i < $((transmitted_speed / 10)); i++)); do
        if (( $i == 45 )); then
            # max number of squares
            break
        fi
        printf "▇"
    done
    printf "\n"

    last_bytes_received=$bytes_received
    last_bytes_transmitted=$bytes_transmitted

    # CPU Usage
    echo "-------------------------------------------------------------------------------------------"
    echo "CPU Usage:"

    cpu_sums=($(cat /proc/stat | grep -E "cpu[0-9]+" | awk '{sum = 0; for(i = 2; i <= NF; i++) sum += $i; print sum}'))
    cpu_sums_deltas=()
    for ((i = 0; i < $cpu_count; i++)); do
        delta=$((${cpu_sums[i]} - ${cpu_last_sums[i]}))
        cpu_sums_deltas+=("$delta")
    done

    cpu_idles=($(cat /proc/stat | grep -E "cpu[0-9]+" | awk '{ print $5 }'))
    cpu_idles_deltas=()
    for ((i = 0; i < $cpu_count; i++)); do
        delta=$((${cpu_idles[i]} - ${cpu_last_idles[i]}))
        cpu_idles_deltas+=("$delta")
    done

    for ((i = 0; i < $cpu_count; i++)); do
        cpu_used=$((${cpu_sums_deltas[i]} - ${cpu_idles_deltas[i]}))
        cpu_usage=$(echo "scale=6; 100 * $cpu_used / ${cpu_sums_deltas[i]}" | bc)
        cpu_speed=$(cat /proc/cpuinfo | grep "cpu MHz" | awk '{print $4}' | head -n $(($i+1)) | tail -n 1)
        cpu_speed=$(echo "scale=6; $cpu_speed * $cpu_usage / 100" | bc)
        printf "%s: %f%% %fMHz\n" ${cpu_names[i]} $cpu_usage $cpu_speed
    done

    cpu_last_sums=$cpu_sums
    cpu_last_idles=$cpu_idles

    # Uptime
    uptime_in_seconds=$(cat /proc/uptime | awk -F '.' '{ print $1 }') # no fractional part
    echo "-------------------------------------------------------------------------------------------"
    echo "Uptime:"
    display_time $uptime_in_seconds

    # Load average
    echo "-------------------------------------------------------------------------------------------"
    printf "Load average in the last minute: %f\n" $(cat /proc/loadavg | awk '{ print $1 }')


    # Memory usage
    echo "-------------------------------------------------------------------------------------------"
    max_memory=$(cat /proc/meminfo | grep MemTotal | awk '{ print $2 }')
    free_memory=$(cat /proc/meminfo | grep MemAvailable | awk '{ print $2 }')
    used_memory=$(($max_memory - $free_memory))
    printf "Current memory usage: %s/%s\n" $(convert_bytes $(($used_memory * 1024))) $(convert_bytes $(($max_memory * 1024)))

    sleep 1
done
