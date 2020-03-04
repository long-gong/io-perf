#!/usr/bin/env bash

set -e

make clean
make


res_filename="res.csv"


for m in 1 10 20 50 60 100
do
    echo 3 | sudo tee /proc/sys/vm/drop_caches
    free -h
    n=10000000
    echo "n = $n, m = $m"
    ./io_perf -n $n -m $m | tee $res_filename
    free -h



    echo 3 | sudo tee /proc/sys/vm/drop_caches
    free -h
    n=100000
    echo "n = $n, m = $m"
    ./io_perf -n $n -m $m | tee -a $res_filename
    free -h

    echo 3 | sudo tee /proc/sys/vm/drop_caches
    free -h
    n=1000000
    echo "n = $n, m = $m"
    ./io_perf -n $n -m $m | tee -a $res_filename
    free -h
done

