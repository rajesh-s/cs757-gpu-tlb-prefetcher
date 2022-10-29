## Semester Plan  
## Doc Updated: 221027

Questions for Rajesh
- How much focus on MCM-GPU? 
- We need to narrow down our 5 steps? 

Before Oct 31: 

* Week of Oct 31 to Nov 6, Nov 7 to 13 (2 weeks):
     * Start on reproducing Valkyrie model using gem5:
          * baseline virtual memory system
         - Spatial locality: ring interconnect modelling in gem5
         - Temporal Locality: add a Locality Detection Table and Prefetching mechanism 
     1B Characterize compute and memory bound workloads TLB sharing patterns on GPU 
         - using gem5 chiplet GPU model that Rajesh will point to
         - Find out how much sharing is there, what can we do? 

Monday: Vishnu walks through running gem5 GPU stuff
1A Vishnu, Rutwik (all later)
1B Lipika, Rajesh
On the side: Rutwik to talk to Matt/Preyesh/Rajesh about getting AMD benchmarks running with gem5 GPU

* Nov 14 to Nov 20: 
* Nov 21 to Nov 27:
* Nov 28 to Dec 4:
* Dec 5 to Dec 11:

        
### Task list we originally proposed
2. Characterize TLB performance and locality patterns with diverse compute and
memory bound workloads. Analyze results and identify cases where TLB sharing
mechanisms are inefficient or virtual memory is selectively disabled for pathological
access patterns.
3. Using design space exploration, determine the trade-offs in parameters such as TLB
size, associativity, ports, non-blocking behavior by hiding miss latency through
swapping another warp that could have TLB hits; page-table walker scheduling
specific to the lane-based designs in GPUs.
4. Explore possibility of using a different interconnect topology (tree or butterfly as
opposed to ring)
5. Explore the implications of MCM’s non-uniformity on the GPU’s virtual memory
