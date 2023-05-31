#!/bin/bash
file="/users/Jonus225/single-server-etrace/.data_labels"
labels_names="/users/Jonus225/single-server-etrace/.data_labels_names"
gapbs_dir="/users/Jonus225/single-server-etrace/benchmarks/gapbs/build"
signal_dir="/users/Jonus225/single-server-etrace/benchmarks/tests/signal/build"
graph500_dir="/users/Jonus225/single-server-etrace/benchmarks/graph500/build"
output_folder="./data"
rapl_folder="./data/rapl"
data_folder="./data/data"
human_readable_file="/users/Jonus225/single-server-etrace/.human_readable_labels"

rm -rf $output_folder
mkdir $output_folder
mkdir $rapl_folder
mkdir $data_folder

cmd_starter="sudo perf stat "

# create a local array for actual machine label names to add into the perf stat command
cur_labels=()

# parse all current machine counter labels into a file called .machine_labels
sudo perf stat -a -d -d -d sleep 1 2> .machine_labels

truncate -s 0 "$file"

# loop through .data_labels_names, for every type of label, see if any of them matches a label
# in the .machine_labels file. If so, break, and add that label into the cur_labels array 
while IFS= read -r label
do
    # split the label line into different names based on commas
    IFS=',' read -ra label_names <<< "$label"

    found=false

    human_readable_name="${label%%,*}"

    # loop through each name
    for name in "${label_names[@]}"
    do
        # loop through .machine_labels file
        while IFS= read -r machine_label
        do
            if [[ "$machine_label" == *"$name"* ]]; then
                found=true
                cur_labels+=("$name")
                printf "%s\n" "$human_readable_name" >> "$human_readable_file"
                break
            fi
        done < .machine_labels
        if [[ "$found" == true ]]; then
            break
        fi
    done

done < $labels_names

# add cur_labels one by one to cmd_starter
for label in "${cur_labels[@]}"
do
    cmd_starter+="-e ${label} "
done

cmd_starter+="taskset -c 0 nice -n -20 "

for entry in `ls $gapbs_dir`
do
    $cmd_starter $gapbs_dir/$entry -g 20 -n 2 1> /dev/null 2> $output_folder/${entry}_data
done

# for entry in `ls $signal_dir`
# do
#      $cmd_starter $signal_dir/$entry 1> /dev/null 2> $output_folder/$entry
# done

#for entry in `ls $graph500_dir`
# do
    # echo $entry
    # $cmd_starter mpirun --allow-run-as-root --mca orte_base_help_aggregate 0 $graph500_dir/$entry 5 1> out 2> $output_folder/${entry}_5
#      $cmd_starter mpirun --allow-run-as-root --mca orte_base_help_aggregate 0 $graph500_dir/$entry 7 1> /dev/null 2> $output_folder/${entry}_7
#      $cmd_starter mpirun --allow-run-as-root --mca orte_base_help_aggregate 0 $graph500_dir/$entry 10 1> /dev/null 2> $output_folder/${entry}_10
    # $cmd_starter mpirun --allow-run-as-root --mca orte_base_help_aggregate 0 $graph500_dir/$entry 5 1> out 2> $output_folder/${entry}_5
#      $cmd_starter mpirun --allow-run-as-root --mca orte_base_help_aggregate 0 $graph500_dir/$entry 7 1> out 2> $output_folder/${entry}_7
#      $cmd_starter mpirun --allow-run-as-root --mca orte_base_help_aggregate 0 $graph500_dir/$entry 10 1> out 2> $output_folder/${entry}_10
#done

mv *_out $rapl_folder
mv $output_folder/*_data $data_folder

# sed -i "s/J/ /g" $output_folder/*
find "$output_folder" -type f ! -path "$output_folder/rapl/*" -exec sed -i "s/J/ /g" {} \;

# sed -i "3,24d" $output_folder/err_*

# put the labels we are using into .data_labels file for generating graphs
printf "%s\n" "${cur_labels[@]}" > "$file"

rm -rf $data_folder/bc_out_data