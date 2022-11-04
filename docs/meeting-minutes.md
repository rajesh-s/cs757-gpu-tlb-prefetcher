# Meeting minutes

## 221104

Agenda:
Baseline system configuration for the project

From the Valkyrie paper - GPU System configuration
| Component         | Configuration                                   | Quantity                          |
|-------------------|-------------------------------------------------|-----------------------------------|
| CU                | 1 GHz                                           | 64                                |
| L1 Vector Cache   | 16KB, 4-way, 5-cycle latency, LRU               | 64                                |
| L1 Inst Cache     | 32KB, 4-way, 5-cycle latency, LRU               | 1 per SA (1 Inst cache per 4 CUs) |
| L1 Scalar Cache   | 16KB, 4-way, 5-cycle latency, LRU               | 1 per SA                          |
| L2 Cache          | 256KB, 16-way, 8-cycle latency                  | 8                                 |
| DRAM              | 512MB HBM, 100-cycle latency                    | 8                                 |
| L1 TLB            | 1 set, 128-way, 1-cycle latency, LRU            | 64                                |
| L2 TLB            | 32 sets, 16-way, 10-cycle latency, 2 ports, LRU | 1                                 |
| IOMMU             | 8 PTWs, 150-cycle latency                       | -                                 |
| Intra-GPU Network | Single-stage XBar                               | 1                                 |

+ TLB miss latencies only available in FS mode on gem5
+ gem5 - need to add latency in SE mode
+  


## 221017

_Agenda:_ 
Project Topic and Proposal finalization(?)

_Discussion_
- **COUP for GPUs = LAB**
  - Might be a steep learning curve for GPU coherence
  - Vishnu checked out the Ruby model and said it is still manageable
- **Effect of prefetching on TLB-sensitive workloads**
  - Workloads with lot of page faults, can sizes be run-time dynamic
  - Inter-L1 TLB locality - look at this paper https://dl.acm.org/doi/10.1145/3410463.3414639
- **Directory Coherence: Security + Size reduction (SecDir + SCD)**
  - https://ieeexplore.ieee.org/document/6168950
  - https://ieeexplore.ieee.org/document/8980313
  - Combining the two ideas to analyse area and security stuff for coherence directories. 
- **Heterosync**
  - Adding new locks to the benchmark

**Left field idea:**
  - Libraries that execute compiled CUDA code to split the CUDA binary into CPU stream, GPU steam.
  - Survey of heterogeneous computing - https://www.sciencedirect.com/science/article/pii/S2210537917303311 
  - Take an application and write CPP code to optimize this CPU-GPU distribution.
  - More of an HPC assignment than 757? Ambitious enough for Josh to accept it as project proposal?

## 220929

Agenda:

-	Narrow down 1-2 topics for the 3-paper summary due on Oct 5. This will serve as the literature survey too and hopefully we can all take up unique papers to save time and present the findings to the others
-	Try to scroll through the recent program of any of the conferences listed here to find topics of relevance to 757: https://github.com/rajesh-s/computer-engineering-resources#computer-architecture--systems
We will also do this during the meeting


- Reducing overheads in Coherence protocols - power/energy/latency etc (Rutwik)
  -   Dynamic Last-Level Cache Allocation to Reduce Area and Power Overhead in Directory Coherence Protocols (2012)
  -   DASC-DIR: a low-overhead coherence directory for many-core processors (2014/2015)
  -   Multi-grain coherence directories, Jason Zebchuk; Babak Falsafi; Andreas Moshovos (2013)
  -   SPATL: Honey, I Shrunk the Coherence Directory (2011)

- Security+Coherence (Lipika)
  - SecDir: A Secure Directory to Defeat Directory Side-Channel Attacks

- Coherence multi-core/ Memory interactions GPU-specific
  - SecDir: A Secure Directory to Defeat Directory Side-Channel Attacks
  - ...

- Virtual memory (MMU) - Apply cache/prefetcher (earlier for data) observations to TLB (page translations)
  - ...
