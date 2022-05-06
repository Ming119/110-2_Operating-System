# [2966473] 110-2 Operating System

## Homework Assignment #2

### 108590050 李浩銘

### Written exercises

#### Chap 7

7.6: In a real computer system, neither the resources available nor the demands of processes for resources are consistent over long periods (months). Resources break or are replaced, new processes come and go, and new resources are bought and added to the system.

- If deadlock is controlled by the banker’s algorithm, which of the following changes can be made safely (without introducing the possibility of deadlock), and under what circumstances?  
(a) Increase Available (new resources added).
>

(b) Decrease Available (resource permanently removed from system).
>

(c) Increase Max for one process (the process needs or wants more resources than allowed).
>

(d) Decrease Max for one process (the process decides that it does not need that many resources).
>

(e) Increase the number of processes.
>

(f) Decrease the number of processes.
>

7.13: Consider the following snapshot of a system:

|    | Allocation <br /> A B C D| Max <br /> A B C D | Available <br /> A B C D|
|:--:|:-------:|:-------:|:-------:|
| P0 | 2 0 0 1 | 4 2 1 2 | 3 3 2 1 |
| P1 | 3 1 2 1 | 5 2 5 2 |         |
| P2 | 2 1 0 3 | 2 3 1 6 |         |
| P3 | 1 3 1 2 | 1 4 2 4 |         |
| P4 | 1 4 3 2 | 3 6 6 5 |         |

- Answer the following questions using the banker’s algorithm:  
(a) Illustrate that the system is in a safe state by demonstrating an order in which the processes may complete.
>

(b) If a request from Process P1 arrives for (1,1,0,0), can the request be granted immediately?
>

(c) If a request from Process P4 arrives for (0,0,2,0), can the request be granted immediately?
>

7.15: A single-lane bridge connects the two Vermont villages of North Tunbridge and South Tunbridge. Farmers in the two villages use this bridge to deliver their produce to the neighbor town.

- The bridge can become deadlocked if a northbound and a southbound farmer get on the bridge at the same time. (Vermont farmers are stubborn and are unable to back up.)
- Using semaphores and/or mutex locks, design an algorithm in pseudocode that prevents deadlock.
- Initially, do not be concerned about starvation (the situation in which northbound farmers prevent southbound farmers from using the bridge, or vice versa).
>

#### Chap 8

8.1: Explain the difference between internal and external fragmentation.
>

8.9: Compare paging with segmentation with respect to how much memory the address translation structures require to convert virtual addresses to physical addresses.
>

8.16: Consider a computer system with a 32-bit logical address and 4KB page size. The system supports up to 512MB of physical memory. How many entries are there in each of the following?  
(a) A conventional single-level page table
>

(b) An inverted page table
>

#### Chap 9

9.8: Consider the following page reference string:`7, 2, 3, 1, 2, 5, 3, 4, 6, 7, 7, 1, 0, 5, 4, 6, 2, 3, 0, 1`.  
Assume demand paging with three frames, how many page faults would occur for the following replacement algorithms?  
(a) LRU replacement
>

(b) FIFO replacement
>

(c) Optimal replacement
>

9.11: Discuss situations in which the least frequently used (LFU) page-replacement algorithm generates fewer page faults than the least recently used (LRU) page-replacement algorithm. Also discuss under which circumstances the opposite holds.
>

9.17: A page-replacement algorithm should minimize the number of page faults. We can achieve this minimization by distributing heavily used pages evenly over all of memory, rather than having them compete for a small number of page frames. We can associate with each page frame a counter of the number of pages associated with that frame. Then, to replace a page, we can search for the page frame with the smallest counter.  
(a) Define a page-replacement algorithm using this basic idea. Specifically address these problems:
> (i) What is the initial value of the counters?
>

> (ii) When are counters increased?
>

> (iii) When are counters decreased?
>

> (iv) How is the page to be replaced selected?
>

(b) How many page faults occur for your algorithm for the following reference string with four page frames?

- `1,2,3,4,5,3,4,1,6,7,8,7,8,9,7,8,9,5,4,5,4,2`.
>

(c) What is the minimum number of page faults for an optimal page-replacement strategy for the reference string in part(b) with four page frames?
>
