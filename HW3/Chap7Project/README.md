# [2966473] 110-2 Operating System

## Homework Assignment #2

### Programming Project

#### Chap.7 Project Banker’s Algorithm

- Write a **multithreaded** program that implements the *banker’s algorithm* discussed in Section 7.5.3. This assignment combines three topics: (1) multithreading (2) preventing race conditions (3) deadlock avoidance.
- Create n customer threads that request and release resources from the bank. The customers will continually loop, requesting and then releasing random numbers of resources. The banker will grant a request if it satisfies the safety algorithm.
- Since multiple threads will concurrently access shared data, access must be controlled through mutex locks to prevent race conditions.
- You should invoke your program by passing the number of resources of each type on the command line.

#### Team Member

- 108590004 謝宗麟
- 108590029 朱欣雨
- 108590049 符芷琪
- 108590050 李浩銘

### Development Environment

- Operating System: Ubuntu 18.04.6 LTS
- Kernel Version: 5.4.0-104-generic
- Compiler Version: gcc 7.5.0

### Build

To compile the source files

```bash
make
```

To clean the object and binary files

```bash
make clean
```

### Usage
