# [2966473] 110-2 Operating System

## Homework Assignment #1

### 108590050 李浩銘

#### Programming problem 3.20

Design a file-copying program named filecopy using ordinary pipes. 
- This program will be passed two parameters: the name of the file to be copied, and the name of the copied file
- The program will then create an ordinary pipe and write the contents of the file to be copied to the pipe
- The child process will read this file from the pipe and write it to the destination file

For example, if we invoke the program as follows:
- filecopy input.txt copy.txt
- The file input.txt will be written to the pipe. The child process will read the contents of this file and write it to the destination file copy.txt. 

You may write this program using either UNIX or Windows pipes.

### Development Environment
- Operating System: Ubuntu 18.04.6 LTS
- Kernel Version: 5.4.0-104-generic
- Compiler Version: gcc 7.5.0

### Build
To compile the source files
```bash
$ make
```

To clean the object and binary files
```bash
$ make clean
```

### Usage
```bash
$ ./bin/filecopy -h
$ ./bin/filecopy --help
```

```bash
$ ./bin/filecopy <src> <dest>
```

### Execution snapshot
First thing first, let's look at the `src/filecopy.c`, I define the size of buffer as 64 bytes.
```c
#define BUF_SIZE 64
```

Therefore, I create a text file `src.txt` with 63 bytes of character and 1 byte of new line character `\n`.

![img](./doc/strace1.png)

As the picture show above, the program will read the source file and write to the destination file **once**. After that, the program read `EOF` then close those two files.

![img](./doc/strace2.png)

Here, I create a text file `src.txt` with 127 bytes of character and 1 byte of new line character `\n`. As expect, the program will read the source file and write to the destination file **twice**. After that, the program read `EOF` then close those two files.

Copy successfully 

![img](./doc/simpleTest.png)


#### Error checking