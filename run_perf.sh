#!/bin/bash
file=".data_labels"
gapbs_dir="/homes/sys/suneja/treehouse/single-server-etrace/benchmarks/gapbs/build"
msr_dir="/homes/sys/suneja/treehouse/single-server-etrace/benchmarks/tests/msr/build"
graph500_dir="/homes/sys/suneja/treehouse/single-server-etrace/benchmarks/graph500/build"
output_folder="./data"

cmd_starter="sudo perf stat "

while IFS= read -r var 
do
    cmd_starter+="-e ${var} "
done < $file

for entry in `ls $gapbs_dir`
 do
     $cmd_starter $gapbs_dir/$entry -g 10 -n 1 1> /dev/null 2> $output_folder/$entry
done

for entry in `ls $msr_dir`
 do
     $cmd_starter $msr_dir/$entry 1> /dev/null 2> $output_folder/$entry
done

for entry in `ls $graph500_dir`
 do
     $cmd_starter mpirun --allow-run-as-root --mca orte_base_help_aggregate 0 $graph500_dir/$entry 5 1> /dev/null 2> $output_folder/$entry
done

sed -i "s/J/ /g" $output_folder/*
