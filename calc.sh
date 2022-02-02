#!/bin/bash

# read -p 'Username: ' username
# read -p 'Data folder: ' data_file
read -p 'Path to files: ' code_folder
read -p 'Path to data: ' data_folder
read -p 'Flags: ' flags

python3 $code_folder/generate_csv.py $data_folder

python3 $code_folder/linear_solver2.py $data_folder

./$code_folder/eqn2/build/fifth -$flags < $code_folder/eqn2/inputs/temp ##TODO: edit this to generate the temp file
