#!/bin/bash
file=".sse_config"
declare -a a

while IFS= read -r var 
do
    a+=($var)
done < $file

if [ ${#a[@]} -ne 5 ]
then
    echo "Please give correctly formatted .sse_config file. Look at README for details"
    exit
fi


if [[ ${a[3]} =~ "g" ]]
then 
    echo "woooo"
else
    echo ${a[3]}
fi
