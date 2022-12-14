#!/bin/bash

echo "Benchmark Root:   Arg1: $1";
echo "Benchmark Name:   Arg2: $2";
first=$1
second=$2
shift 2
echo "Options:          Arg3: $*";
opts="$@"


export LD_LIBRARY_PATH=/usr/lib
mkdir -p m5out

build/GCN3_X86/gem5.opt configs/example/apu_se.py -n 3 --num-compute-units=64 --cu-per-sa=16 --num-gpu-complex=4 --reg-alloc-policy=dynamic --num-tccs=8 --bw-scalor=8 --num-dirs=64 --mem-size=16GB --mem-type=HBM_2000_4H_1x64 --vreg-file-size=16384 --sreg-file-size=800 --tcc-size=4MB --gpu-clock=1801MHz --ruby-clock=1000MHz --TCC_latency=121  --TCP_latency=16 --max-coalesces-per-cycle=10 --sqc-size=16kB --benchmark-root="$first" -c $second --L1TLBentries=4 --L2TLBentries=16 --L1TLBassoc=1 --L2TLBassoc=1 --L3TLBentries=1 --L3TLBassoc=1 --options="$opts"
