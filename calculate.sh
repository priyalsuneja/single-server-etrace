#!/bin/bash

read -p 'Username: ' username
read -p 'Data folder: ' data_file

python3 $data_file/generate_csv.py $username $data_file

python3 $data_file/linear_solver2.py $username $data_file

python3 $data_file/calc_formulae.py $username $data_file
