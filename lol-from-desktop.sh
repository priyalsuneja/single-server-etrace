#!/bin/bash
spec_dir="/scratch/suneja/cpu2017/benchspec/CPU/"
graph500_dir="/scratch/suneja/graph500/build/"
gapbs_dir="~/gapbs/build/"


source shrc 
for d in `ls $spec_dir` ; do 
    if [[ -d "$spec_dir/$d" ]]; then
#         echo "$d
#         echo "${d:0:3}"
        f="${d:0:3}"
        taskset -c 2 ../a.out $f & 
        mypid=$!
        perf stat -e L1-icache-load-misses -e cycles -e cycle_activity.stalls_total -e instructions -e l2_rqsts.miss -e dTLB-load-misses -e L1-dcache-load-misses -e iTLB-load-misses -e LLC-load-misses taskset -c 0 nice -n -20 runcpu --config=priyal.cfg --action=run $f 2> "${f}_err"
        kill $mypid
    fi
done 

