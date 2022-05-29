# [2966473] 110-2 Operating System

## Homework Assignment #4

### 108590050 李浩銘

### Written exercises

#### Chap 11

11.2: Contrast the performance of the three techniques for allocating disk blocks (contiguous, linked, and indexed) for both sequential and random file access.
> `contiguous`: Works very well on both sequential and random file access. Since the file is stored contiguously, we can just traversing the contiguous disk blocks and determine the adjacent diskblock containing the position we wish to seek to.  
> `linked`: Works better on sequentail file access. In sequentail file access, we can simply following the links from oneblock to the next. However in random file access, it may require following the links to several disk blocksuntil we arrive at the intended seek point of the file.  
> `indexed`: Works well on both sequential and random file access. We can sequentially accessing each index and determine the index associated withthe disk block containing the position we wish to seek to.

11.8: Consider a file system that uses inodes to represent files. Disk blocks are 8KB in size, and a pointer to a disk block requires 4 bytes. This file system has 12 direct disk blocks, as well as single, double, and triple indirect disk blocks. What is the maximum size of a file that can be stored in this file system?
> number of pointers/block = 8KB/4B = 8192btyes/4btyes = 2048  
> Size of 12 direct disk blocks: 12 $\times$ 8KB = 96KB  
> Size of single indirect disk block: 2048 $\times$ 8KB = 16MB  
> Size of double indirect disk block: 2048 $\times$ 2048 $\times$ 8KB = 32GB  
> Size of triple indirect disk block: 2048 $\times$ 2048 $\times$ 2048 $\times$ 8KB = 64TB  
> Therefore, the maximun size of a file that can be stored in this file system is 96KB + 16MB + 32GB + 64TB $\approx$ 64TB

#### Chap 12

12.3: Suppose that a disk drive has 5,000 cylinders, numbered 0 to 4,999. The drive is currently serving a request at cylinder 2,150, and the previous request was at cylinder 1,805. The queue of pending requests, in FIFO order, is 2,069, 1,212, 2,296, 2,800, 544, 1,618, 356, 1,523, 4,965, 3,681 Starting from the current head position, what is the total distance (in cylinders) that the disk arm moves to satisfy all the pending requests, for each of the following disk-scheduling algorithms?

- (a) FCFS
- (b) SSTF
- (c) SCAN
- (d) C-SCAN

> |       | FCFS  | SSTF | SCAN | C-SCAN |
> |:-----:|:-----:|:----:|:----:|:------:|
> | 1     | 2150  | 2150 | 2150 | 2150   |
> | 2     | 2069  | 2069 | 2296 | 2296   |
> | 3     | 1212  | 2296 | 2800 | 2800   |
> | 4     | 2296  | 2800 | 3681 | 3681   |
> | 5     | 2800  | 3681 | 4965 | 4965   |
> | 6     | 544   | 4965 | 4999 | 4999   |
> | 7     | 1618  | 1618 | 2069 | 0      |
> | 8     | 356   | 1523 | 1618 | 356    |
> | 9     | 1523  | 1212 | 1523 | 544    |
> | 10    | 4965  | 544  | 1212 | 1212   |
> | 11    | 3681  | 356  | 544  | 1523   |
> | 12    |       |      | 356  | 1618   |
> | 13    |       |      |      | 2069   |
> | Total | 13011 | 7586 | 7492 | 9917   |

12.10: Compare the throughput achieved by a RAID level 5 organization with that achieved by a RAID level 1 organization.
(a) Read operations on single blocks.
> RAID 5 comprising of a parity block for every set of four blocks spread over five disks can support four to five operations simultaneously. A RAID 1 comprising of two disks can support two simultaneous operations.

(b) Read operations on multiple contiguous blocks.
> RAID 5 achieves greater bandwidth for accesses to multiple contiguous blocks since the adjacent blocks could be simultaneously accessed. Such bandwidth improvements are not possible in RAID 1.

12.12: Assume that you have a mixed configuration comprising disks organized as RAID level 1 and RAID level 5 disks. Assume that the system has flexibility in deciding which disk organization to use for storing a particular file. Which files should be stored in the RAID level 1 disks and which in the RAID level 5 disks in order to optimize performance?
> For those files are frequently read other than write should be stored in RAID 5, and conversely for those files are frequently write other than read should be stored in RAID 1.

### Programming exercises

#### Programming problems

- [Chap 11.13](./Chap11.13/README.md)
- [Chap 12.16](./Chap12.16/README.md)
