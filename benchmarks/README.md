# Running benchmarks with gem5

## SE mode

Cases:

- baseline/ : baseline gem5 gpu run with default configuration
- new_design/ : LDT introduced design
- new_design_2/ : LDT introduced with L1 TLB bug fix
- new_design_3/ : Reduced L1/L2 TLB size to minimal to see if it makes a difference with LDT
- new_design_4/ : 64/128 entries on L1/L2 TLB, L3 TLB limited to 1
