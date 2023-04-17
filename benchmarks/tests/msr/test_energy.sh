#!/bin/bash
temp=".temp_output"
aslr="/proc/sys/kernel/randomize_va_space"

rm -rf $temp
mkdir $temp

# turn off aslr temporarily
echo 0 | tee $aslr

# run binary - make this less hard coded later
./build/mm_signal > $temp/output.txt

# get the elf file
# readelf -s ./build/mm_signal > $temp/elf.txt

# run python stuffs
python3 compute_energy.py

# get addresses


# turn aslr back on
echo 2 | tee $aslr
