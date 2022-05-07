# [2966473] 110-2 Operating System

## Homework Assignment #3

### 108590050 李浩銘

#### Programming problem 8.25

Assume that a system has a 32-bit virtual address with a 4-KB page size. Write a program that is passed a virtual address (in decimal) on the command line and have it output the page number and offset for the given address.

As an example, your program would run as follows:
> ./a.out 19986

Your program would output:
> The address 19986 contains:
> page number = 4
> offset = 3602

Writing this program will require using the appropriate data type to store 32 bits. We encourage you to use unsigned data types as well.

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

```bash
./bin/main <address>
```

### Execution snapshot

![img](./doc/execution.png)
