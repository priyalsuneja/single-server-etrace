#!/bin/bash

# read -p 'Username: ' username
# read -p 'Data folder: ' data_file
read -p 'Path to files: ' code_folder
read -p 'Path to data: ' data_folder

python3 $code_folder/generate_csv.py $data_folder

python3 $code_folder/linear_solver2.py $data_folder

python3 $code_folder/calc_formulae.py $data_folder < $code_folder/temp ##TODO: edit this to generate the temp file
