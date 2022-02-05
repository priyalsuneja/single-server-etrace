#TODO: full pipeline
# get as input: folder with files that need to be analyzed
# 1. run script to generate perf outputs
# 2. read perf outputs to generate csv files 
# 3. read csv file to linearly solve
# 4. have file that reads coefficients.csv to read coeff and reads the csv file
# to get input to different values & calculates result
#!/bin/bash

# read -p 'Username: ' username
# read -p 'Data folder: ' data_file
read -p 'Path to code: ' code_folder
read -p 'Path to data: ' data_folder
read -p 'Flags: ' flags

python3 $code_folder/generate_csv.py $data_folder $code_folder

python3 $code_folder/linear_solver2.py $code_folder

./$code_folder/fifth -$flags < $code_folder/temp >> $code_folder/out
