# [2966473] 110-2 Operating System

## Homework Assignment #2

### 108590050 李浩銘

### Written exercises

#### Chap 7

7.6: In a real computer system, neither the resources available nor the demands of processes for resources are consistent over long periods (months). Resources break or are replaced, new processes come and go, and new resources are bought and added to the system.

- If deadlock is controlled by the banker’s algorithm, which of the following changes can be made safely (without introducing the possibility of deadlock), and under what circumstances?

(a) Increase Available (new resources added).
> This can be made safely in any circumstances.

(b) Decrease Available (resource permanently removed from system).
> This can introduce the possibility of deadlock if there were a certain number of availabe resources.

(c) Increase Max for one process (the process needs or wants more resources than allowed).
> This can introduce the possibility of deadlock.

(d) Decrease Max for one process (the process decides that it does not need that many resources).
> This can be made safely in any circumstances.

(e) Increase the number of processes.
> This can be made safely if resources were allocated to the new processes.

(f) Decrease the number of processes.
> This can be made safely in any circumstances.

7.13: Consider the following snapshot of a system:

|    | Allocation <br /> A B C D | Max <br /> A B C D | Available <br /> A B C D |
|:--:|:-------:|:-------:|:-------:|
| P0 | 2 0 0 1 | 4 2 1 2 | 3 3 2 1 |
| P1 | 3 1 2 1 | 5 2 5 2 |         |
| P2 | 2 1 0 3 | 2 3 1 6 |         |
| P3 | 1 3 1 2 | 1 4 2 4 |         |
| P4 | 1 4 3 2 | 3 6 6 5 |         |

- Answer the following questions using the banker’s algorithm:

(a) Illustrate that the system is in a safe state by demonstrating an order in which the processes may complete.
> |    | Need <br /> A B C D | Finish |
> |:--:|:-------------------:|:------:|
> | P0 | 2 2 1 1             | False  |
> | P1 | 2 1 3 1             | False  |
> | P2 | 0 2 1 3             | False  |
> | P3 | 0 1 1 2             | False  |
> | P4 | 2 2 3 3             | False  |
>
> For P0:
> > Need(P0) <= Available  
> > Availabe += Allocation(P0) // Availabe = (5, 3, 2, 2)  
> > Finish(P0) = True
> > |    | Need <br /> A B C D | Finish |
> > |:--:|:-------------------:|:------:|
> > | P0 | 2 2 1 1             | True   |
> > | P1 | 2 1 3 1             | False  |
> > | P2 | 0 2 1 3             | False  |
> > | P3 | 0 1 1 2             | False  |
> > | P4 | 2 2 3 3             | False  |
>
> For P1:
> > Need(P1) > Available  
> > P1 have to wait
> > |    | Need <br /> A B C D | Finish |
> > |:--:|:-------------------:|:------:|
> > | P0 | 2 2 1 1             | True   |
> > | P1 | 2 1 3 1             | False  |
> > | P2 | 0 2 1 3             | False  |
> > | P3 | 0 1 1 2             | False  |
> > | P4 | 2 2 3 3             | False  |
>
> For P2:
> > Need(P2) > Available  
> > P2 have to wait
> > |    | Need <br /> A B C D | Finish |
> > |:--:|:-------------------:|:------:|
> > | P0 | 2 2 1 1             | True   |
> > | P1 | 2 1 3 1             | False  |
> > | P2 | 0 2 1 3             | False  |
> > | P3 | 0 1 1 2             | False  |
> > | P4 | 2 2 3 3             | False  |
>
> For P3:
> > Need(P3) <= Available  
> > Availabe += Allocation(P3) // Availabe = (6, 6, 3, 4)  
> > Finish(P3) = True
> > |    | Need <br /> A B C D | Finish |
> > |:--:|:-------------------:|:------:|
> > | P0 | 2 2 1 1             | True   |
> > | P1 | 2 1 3 1             | False  |
> > | P2 | 0 2 1 3             | False  |
> > | P3 | 0 1 1 2             | True   |
> > | P4 | 2 2 3 3             | False  |
>
> For P4:
> > Need(P4) <= Available  
> > Availabe += Allocation(P4) // Availabe = (7, 10, 6, 6)  
> > Finish(P4) = True
> > |    | Need <br /> A B C D | Finish |
> > |:--:|:-------------------:|:------:|
> > | P0 | 2 2 1 1             | True   |
> > | P1 | 2 1 3 1             | False  |
> > | P2 | 0 2 1 3             | False  |
> > | P3 | 0 1 1 2             | True   |
> > | P4 | 2 2 3 3             | True   |
>
> For P1:
> >Need(P1) <= Available  
> > Availabe += Allocation(P1) // Availabe = (10, 11, 8, 7)  
> > Finish(P1) = True
> > |    | Need <br /> A B C D | Finish |
> > |:--:|:-------------------:|:------:|
> > | P0 | 2 2 1 1             | True   |
> > | P1 | 2 1 3 1             | True   |
> > | P2 | 0 2 1 3             | False  |
> > | P3 | 0 1 1 2             | True   |
> > | P4 | 2 2 3 3             | True   |
>
> For P2:
> > Need(P2) <= Available  
> > Availabe += Allocation(P2) // Availabe = (12, 12, 8, 10)  
> > Finish(P2) = True
> > |    | Need <br /> A B C D | Finish |
> > |:--:|:-------------------:|:------:|
> > | P0 | 2 2 1 1             | True   |
> > | P1 | 2 1 3 1             | True   |
> > | P2 | 0 2 1 3             | True   |
> > | P3 | 0 1 1 2             | True   |
> > | P4 | 2 2 3 3             | True   |
>
> Order: P0 -> P3 -> P4 -> P1 -> P2

(b) If a request from Process P1 arrives for (1,1,0,0), can the request be granted immediately?
> Arrives(P1) < Need(P1) // (1, 1, 0, 0) < (2, 2, 1, 1)  
> Arrives(P1) < Available // (1, 1, 0, 0) < (3, 3, 2, 1)  
> Available -= Arrives(P1) // Available = (2, 2, 2, 1)  
> Allocation(P1) += Arrives(P1) // Allocation(P1) = (4, 2, 2, 1)  
> => Need(P1) = (1, 0, 3, 1)
>
> |    | Allocation <br /> A B C D | Max <br /> A B C D | Need <br /> A B C D | Available <br /> A B C D |
> |:--:|:-------:|:-------:|:-------:|:-------:|
> | P0 | 2 0 0 1 | 4 2 1 2 | 2 2 1 1 | 2 2 2 1 |
> | P1 | 4 2 2 1 | 5 2 5 2 | 1 0 3 1 |         |
> | P2 | 2 1 0 3 | 2 3 1 6 | 0 2 1 3 |         |
> | P3 | 1 3 1 2 | 1 4 2 4 | 0 1 1 2 |         |
> | P4 | 1 4 3 2 | 3 6 6 5 | 2 2 3 3 |         |
>
> By the Banker's algorithm
> The Order: P0 -> P3 -> P4 -> P1 -> P2

(c) If a request from Process P4 arrives for (0,0,2,0), can the request be granted immediately?
> Arrives(P4) < Need(P4) // (0, 0, 2, 0) <> (2, 2, 3, 3)  
> Arrives(P4) >= Available // (0, 0, 2, 0) >= (3, 3, 2, 1)  
> Therefore, a request from process P4 arrives for (0, 0, 2, 0) cannot be granted immediately.

7.15: A single-lane bridge connects the two Vermont villages of North Tunbridge and South Tunbridge. Farmers in the two villages use this bridge to deliver their produce to the neighbor town.

- The bridge can become deadlocked if a northbound and a southbound farmer get on the bridge at the same time. (Vermont farmers are stubborn and are unable to back up.)
- Using semaphores and/or mutex locks, design an algorithm in pseudocode that prevents deadlock.
- Initially, do not be concerned about starvation (the situation in which northbound farmers prevent southbound farmers from using the bridge, or vice versa).

> ```c
> semaphore accessible = 1;
>
> void enterBridge() {  
>     wait(accessible);
> }
>
> void exitBridge() {
>     signal(accessible);
> }
> ```

#### Chap 8

8.1: Explain the difference between internal and external fragmentation.
> Internal fragmentation: The area occupied by a process but cannot be used by the process. The space is unusable by the system until the process release the space.  
> External fragmentation: Exists when total free memory is enough for the new process but it is not contiguous and cannot satisfy the request. Storage is fragmented into small holes.

8.9: Compare paging with segmentation with respect to how much memory the address translation structures require to convert virtual addresses to physical addresses.
> Paging requires more memory overhead than segmentation to maintain the translation structures. Paging requires a entry for each page, while segmentation requires only two registers for each segment.

8.16: Consider a computer system with a 32-bit logical address and 4KB page size. The system supports up to 512MB of physical memory. How many entries are there in each of the following?  
(a) A conventional single-level page table
> 4KB = 4096 bits = 2^(12)  
> Therefore, 2^(32) / 2^(12) = 2^(20) entries are there.

(b) An inverted page table
> 4KB = 4096 bits = 2^(12)  
> 5MB = 5120KB = 2^(29)
> Therefore, 2^(29) / 2^(12) = 2^(17) entries are there.

#### Chap 9

9.8: Consider the following page reference string:`7, 2, 3, 1, 2, 5, 3, 4, 6, 7, 7, 1, 0, 5, 4, 6, 2, 3, 0, 1`.  
Assume demand paging with three frames, how many page faults would occur for the following replacement algorithms?  
(a) LRU replacement
> Frames:
> > 7 (faults += 1)  
> > 7, 2 (faults += 1)  
> > 7, 2, 3 (faults += 1)  
> > 2, 3, 1 (faults += 1)  
> > 3, 1, 2  
> > 1, 2, 5 (faults += 1)  
> > 2, 5, 3 (faults += 1)  
> > 5, 3, 4 (faults += 1)  
> > 3, 4, 6 (faults += 1)  
> > 4, 6, 7 (faults += 1)  
> > 4, 6, 7  
> > 6, 7, 1 (faults += 1)  
> > 7, 1, 0 (faults += 1)  
> > 1, 0, 5 (faults += 1)  
> > 0, 5, 4 (faults += 1)  
> > 5, 4, 6 (faults += 1)  
> > 4, 6, 2 (faults += 1)  
> > 6, 2, 3 (faults += 1)  
> > 2, 3, 0 (faults += 1)  
> > 3, 0, 1 (faults += 1)  
> Total faults: 18

(b) FIFO replacement
> Frames:
> > 7 (faults += 1)  
> > 7, 2 (faults += 1)  
> > 7, 2, 3 (faults += 1)  
> > 2, 3, 1 (faults += 1)  
> > 2, 3, 1  
> > 3, 1, 5 (faults += 1)  
> > 3, 1, 5  
> > 1, 5, 4 (faults += 1)  
> > 5, 4, 6 (faults += 1)  
> > 4, 6, 7 (faults += 1)  
> > 4, 6, 7  
> > 6, 7, 1 (faults += 1)  
> > 7, 1, 0 (faults += 1)  
> > 1, 0, 5 (faults += 1)  
> > 1, 0, 5  
> > 0, 5, 4 (faults += 1)  
> > 5, 4, 6 (faults += 1)  
> > 4, 6, 2 (faults += 1)  
> > 6, 2, 3 (faults += 1)  
> > 2, 3, 0 (faults += 1)  
> > 3, 0, 1 (faults += 1)  
> Total faults: 17

(c) Optimal replacement
> Frames:
> > 7 (faults += 1)  
> > 7, 2 (faults += 1)  
> > 7, 2, 3 (faults += 1)  
> > 1, 2, 3 (faults += 1)  
> > 1, 2, 3
> > 1, 5, 3 (faults += 1)  
> > 1, 5, 3
> > 1, 5, 4 (faults += 1)  
> > 1, 5, 6 (faults += 1)  
> > 1, 5, 7 (faults += 1)  
> > 1, 5, 7
> > 1, 5, 7
> > 1, 5, 0 (faults += 1)  
> > 1, 5, 0
> > 1, 4, 0 (faults += 1)  
> > 1, 6, 0 (faults += 1)  
> > 1, 2, 0 (faults += 1)  
> > 1, 3, 0 (faults += 1)  
> Total faults: 13

9.11: Discuss situations in which the least frequently used (LFU) page-replacement algorithm generates fewer page faults than the least recently used (LRU) page-replacement algorithm. Also discuss under which circumstances the opposite holds.
> Consider the sequence of memory accesses in a system that can hold 3 pages in memory: `1 1 2 2 3 4 1`  
> When page 4 is accessed, the LFU page-replacement algorithm will replace page 3. Therefore it will not incur a page fault when page 1 is accessed again. However, the LRU page-replacement algorithm will replace page 1. Therefore it will incur a page fault when page 1 is accessed again.  
> On the another hand, consider another sequence of memory accesses in a system that can also hold 3 pages in memory: `1 1 2 2 3 4 3`  
> When page 4 is accessed, the LFU page-replacement algorithm will replace page 3. Therefore it will incur a page fault when page 3 is accessed again. However, the LRU page-replacement algorithm will replace page 1. Therefore it will not incur a page fault when page 3 is accessed again.

9.17: A page-replacement algorithm should minimize the number of page faults. We can achieve this minimization by distributing heavily used pages evenly over all of memory, rather than having them compete for a small number of page frames. We can associate with each page frame a counter of the number of pages associated with that frame. Then, to replace a page, we can search for the page frame with the smallest counter.  
(a) Define a page-replacement algorithm using this basic idea. Specifically address these problems:
> (i) What is the initial value of the counters?  
> 0

> (ii) When are counters increased?  
> A new page is associated with that frame.

> (iii) When are counters decreased?
> One of the pages associated with that frame is no longer needed

> (iv) How is the page to be replaced selected?
> A page to be replaced is selected as the frame with the smallest counter, with a FIFO queue to break ties.

(b) How many page faults occur for your algorithm for the following reference string with four page frames?

- `1,2,3,4,5,3,4,1,6,7,8,7,8,9,7,8,9,5,4,5,4,2`.

> 14 page faults.

(c) What is the minimum number of page faults for an optimal page-replacement strategy for the reference string in part(b) with four page frames?
> 11 page faults.

9.19: What is the cause of thrashing? How does the system detect thrashing? Once it detects thrashing, what can the system do to eliminate this problem?
> Thrashing is caused by under allocation of the minimum number of pages required by a process, forcing it to continuously page fault.  
> The system can detect thrashing by evaluating the level of CPU utilization as compared to the level of multiprogramming.  
> It can be eliminated by reducing the level of multiprogramming.

### Programming exercises

#### Programming problems

- [Chap 7.17](./Chap7.17/README.md)
- [Chap 8.25](./Chap8.25/README.md)
- [Chap 9.26](./Chap9.26/README.md)

#### Programming projects

- [Chap.7 Project](./Chap7Project/README.md)
