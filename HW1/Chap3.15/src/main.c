/*
 *  Chap3.15/src/main.c
 *
 *  Programming Problem Chap. 3.15
 *
 *  108590050 李浩銘
 */

#define _XOPEN_SOURCE 700   // for ftruncate()

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#ifndef SHARE_MEM_SIZE
#define SHARE_MEM_SIZE 128
#endif

void usage(char *programName)
{
    printf("Usage:\n\t%s <num>\n", programName);
}

void sequence(void* ptr, int n)
{      
    while (n != 1)
    {   
        ptr += sprintf(ptr, "%d, ", n);
        
        n = n%2? 3*n+1: n/2;
    }

    ptr += sprintf(ptr, "%d\n", n);
}

int main(int argc, char *argv[])
{
    if (argc == 2 && !(strcmp(argv[1], "-h") && strcmp(argv[1], "--help")))
    {
        usage(argv[0]);
        exit(EXIT_SUCCESS);
    }

    int num;
    if (argc == 2)
    {
        num = atoi(argv[1]);

    } else
    {   
        printf("Input a positive integer: ");
        scanf("%d", &num);
    }
    
    if (num < 1)
    {
        printf("Please input a positive integer.\n");
        exit(EXIT_FAILURE);
    }

    // Establish the shared-memory object
    int shmFd = shm_open("collatz", O_CREAT | O_RDWR, 0666);
    ftruncate(shmFd, SHARE_MEM_SIZE);
    void* ptr = mmap(0, SHARE_MEM_SIZE, PROT_READ | PROT_WRITE , MAP_SHARED, shmFd, 0);

    // Fork a child process
    pid_t pid = fork();
    if (pid < 0)            // Error Occurred
    {
        perror("Fork Error");
        exit(EXIT_FAILURE);

    } else if (pid == 0)    // Child process
    {
        sequence(ptr, num);

    } else                  // Parent process
    {   
        wait(NULL);
        printf("%s", (char*)ptr);   // Output the contents of shared memory
        shm_unlink("collatz");      // Remove the shared-memory object
    }

    exit(EXIT_SUCCESS);
}