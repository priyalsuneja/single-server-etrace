#!/bin/bash 
file=".sse_config"

declare -a vars

# readarray -t a < $file 
while IFS= read -r var 
do 
    vars+=($var)
done < $file

for val in "${vars[@]}"
do 
    echo $val
done

if [ ${#vars[@]} -ne 4 ]
then
    echo "Please give correctly formatted .sse_config file. Look at README for details"
    exit
fi
