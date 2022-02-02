#!/bin/bash

# read -p 'Username: ' username
# read -p 'Data folder: ' data_file
read -p 'Path to data: ' data_folder

python3 generate_csv.py $data_folder

python3 linear_solver2.py $data_folder

python3 calc_formulae.py $data_folder < $data_folder/temp ##TODO: edit this to generate the temp file
