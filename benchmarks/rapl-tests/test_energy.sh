#!/bin/bash
temp=".temp_output"
aslr="/proc/sys/kernel/randomize_va_space"

rm -rf $temp
mkdir $temp

# $1 is binary (cmd argument)

# turn off aslr temporarily
echo 0 | tee $aslr

# run binary - make this less hard coded later
# ./build/mm_signal > $temp/output.txt

# get the elf file
readelf -s $1 > $temp/elf.txt

# get offset of main
python3 get_main_offset.py

# run binary
$1 > $temp/output.txt

# run python stuffs
python3 parse_output.py

# convert addresses to functions
addr2line -f -e $1 < $temp/addresses.txt > $temp/translated.txt

# clean that up
python3 get_functions.py

python3 compute_energy.py

# turn aslr back on
echo 2 | tee $aslr