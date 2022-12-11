#!/usr/bin/env bash

find  baseline/*/results/m5out/stats.txt |& tee stats_file_path_baseline.txt
rm -rf cumulative_stats_baseline.txt
touch cumulative_stats_baseline.txt
input_file="stats_file_path_baseline.txt"
while read -r line;
do
	echo "$line" >> cumulative_stats_baseline.txt
	grep system.l1_tlb.*localTLBMissRate "$line" >> cumulative_stats_baseline.txt
done < "$input_file"

