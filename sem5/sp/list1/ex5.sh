#!/bin/bash

if [ "$#" -ne 1 ] || [ ! -d "$1" ]; then
    echo -n "Correct directory path was not provided."
    return 1
fi

find "$1" -type f -exec sed -i "s/a/A/g" {} \;
