#!/bin/bash 
file=".sse_config"

readarray -t a < $file 

if [ ${#a[@]} -ne 4 ]
then
    echo "Please give correctly formatted .sse_config file. Look at README for details"
    exit
fi
printf '%s\n' "${a[@]}"
