#!/usr/bin/env bash

set -e

make clean
make 

n=100000
m=100
res_filename="res.csv"

echo "n = $n, m = $m"
./io_perf -n $n -m $m | tee $res_filename

n=10000000
echo "n = $n, m = $m"
./io_perf -n $n -m $m | tee -a $res_filename

