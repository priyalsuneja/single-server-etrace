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
file=".sse_config"

readarray -t a < $file 

if [ ${#a[@]} -ne 4 ]
then
    echo "Please give correctly formatted .sse_config file. Look at README for details"
    exit
fi

mkdir ${a[0]}/.sse_tmp

python3 ${a[0]}/generate_csv.py ${a[1]} ${a[0]}

python3 ${a[0]}/linear_solver2.py ${a[0]}

./${a[0]}/fifth -${a[3]} < ${a[0]}/temp >> ${a[0]}/${a[2]}

rm -rf ${a[0]}/.sse_tmp
