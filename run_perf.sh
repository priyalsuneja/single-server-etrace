#!/bin/bash
file="/homes/sys/suneja/treehouse/single-server-etrace/.data_labels"
gapbs_dir="/homes/sys/suneja/treehouse/single-server-etrace/benchmarks/gapbs/build"
signal_dir="/homes/sys/suneja/treehouse/single-server-etrace/benchmarks/tests/signal/build"
graph500_dir="/homes/sys/suneja/treehouse/single-server-etrace/benchmarks/graph500/build"
# graph500_dir="/homes/sys/suneja/graph500/build"
output_folder="./data"
rapl_folder="./data/rapl"

rm -rf $output_folder
mkdir $output_folder
mkdir $rapl_folder

cmd_starter="sudo perf stat "

while IFS= read -r var 
do
    cmd_starter+="-e ${var} "
done < $file

for entry in `ls $gapbs_dir`
 do
     $cmd_starter $gapbs_dir/$entry -g 20 -n 2 1> /dev/null 2> $output_folder/$entry
done

for entry in `ls $signal_dir`
 do
     $cmd_starter $signal_dir/$entry 1> /dev/null 2> $output_folder/$entry
done

echo $cmd_starter

# for entry in `ls $graph500_dir`
#  do
#      echo $entry
#      $cmd_starter mpirun --allow-run-as-root --mca orte_base_help_aggregate 0 $graph500_dir/$entry 5 1> out 2> $output_folder/${entry}_5
#      $cmd_starter mpirun --allow-run-as-root --mca orte_base_help_aggregate 0 $graph500_dir/$entry 7 1> /dev/null 2> $output_folder/${entry}_7
#      $cmd_starter mpirun --allow-run-as-root --mca orte_base_help_aggregate 0 $graph500_dir/$entry 10 1> /dev/null 2> $output_folder/${entry}_10
#      $cmd_starter mpirun --allow-run-as-root --mca orte_base_help_aggregate 0 $graph500_dir/$entry 5 1> out 2> $output_folder/${entry}_5
#      $cmd_starter mpirun --allow-run-as-root --mca orte_base_help_aggregate 0 $graph500_dir/$entry 7 1> out 2> $output_folder/${entry}_7
#      $cmd_starter mpirun --allow-run-as-root --mca orte_base_help_aggregate 0 $graph500_dir/$entry 10 1> out 2> $output_folder/${entry}_10
# done

mv *_out $rapl_folder

sed -i "s/J/ /g" $output_folder/*
# sed -i "3,24d" $output_folder/err_*
