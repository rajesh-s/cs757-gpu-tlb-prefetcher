import argparse, os
import sys
import subprocess
parser = argparse.ArgumentParser()

#parser.add_argument(
#        '--benchmark',
#        type=str,
#        default='all',
#        help='Name of the microbenchmark',
#)

args = parser.parse_args()

cmd = 'docker run --rm -v $PWD:/home -w /home gcn-gpu gem5/build/GCN3_X86/gem5.opt --debug-flags=GPUTLB --debug-file=trace.out gem5/configs/example/apu_se.py -n 3 --dgpu --gfx-version=gfx803 -c /home/bin/square --num-compute-units=60 --cu-per-sa=15 --num-gpu-complex=4 --reg-alloc-policy=dynamic --num-tccs=8 --bw-scalor=8 --num-dirs=64 --mem-size=16GB --mem-type=HBM_2000_4H_1x64 --vreg-file-size=16384 --sreg-file-size=800 --tcc-size=4MB --gpu-clock=1801MHz --ruby-clock=1000MHz --TCC_latency=121 --L1MissLatency=500 --L2MissLatency=500 --L3MissLatency=500 --L1AccessLatency=150 --L2AccessLatency=200 --L3AccessLatency=250 --L1TLBentries=4 --L2TLBentries=16 --L1TLBassoc=1 --L2TLBassoc=1'
print (cmd)
#subprocess.run(args = cmd, shell=True)
os.system(cmd)

