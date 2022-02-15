#!/bin/bash

#TODO: full pipeline
# get as input: folder with files that need to be analyzed
# 1. run script to generate perf outputs
# 2. read perf outputs to generate csv files 
# 3. read csv file to linearly solve
# 4. have file that reads coefficients.csv to read coeff and reads the csv file
# to get input to different values & calculates result

# read -p 'Path to code: ' code_folder
# read -p 'Path to data: ' data_folder
# read -p 'Output file :' outfile    
# read -p 'Flags: ' flags
# read -p 'Temp folder: ' temp_folder
file=".sse_config"

# readarray -t a < $file 

declare -a a

while IFS= read -r var 
do
    a+=($var)
done < $file

if [ ${#a[@]} -ne 6 ]
then
    echo "Please give correctly formatted .sse_config file. Look at README for details"
    exit
fi

mkdir ${a[4]}

python3 ${a[0]}/generate_csv.py ${a[1]} ${a[4]} ${a[5]}

python3 ${a[0]}/linear_solver.py ${a[4]}

./${a[0]}/fifth -${a[3]} ./${a[4]}/graph_out_one < ./${a[4]}/temp > ${a[2]}

if [[ ${a[3]} =~ "g" ]]
then 
    python3 ${a[0]}/graph_relative_error.py ${a[4]}/graph_out_one ${a[4]}/ipc_input
fi

rm -rf ${a[4]}
