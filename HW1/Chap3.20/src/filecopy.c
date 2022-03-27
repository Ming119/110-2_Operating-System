/*
 *  Chap3.20/src/filecopy.c
 *
 *  Programming Problem Chap. 3.20
 * 
 *  108590050 李浩銘
 * 
 */  

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef BUF_SIZE
#define BUF_SIZE     64
#endif

#define READ_END 0
#define WRITE_END 1

void usage(char *programName)
{
    printf("Usage:\n\t%s <src> <dest>\n", programName);
}

int main(int argc, char *argv[])
{
    if ((argc == 2 && !(strcmp(argv[1], "-h") && strcmp(argv[1], "--help"))) || argc != 3)
    {
        usage(argv[0]);
        exit(EXIT_SUCCESS);
    }

    // Create the pipe
    int fd[2];
    if (pipe(fd) == -1)
    {
        perror("Pipe Error");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid_t pid = fork();
    if (pid < 0)            // Error Occurred
    {
        perror("Fork Error");
        exit(EXIT_FAILURE);

    } else if (pid == 0)    // Child process
    {
        // Close the unused end of the pipe
        close(fd[WRITE_END]);

        // Create output file
        int outFd;
        if ((outFd = open(argv[2], O_EXCL | O_CREAT | O_WRONLY, S_IRWXU | S_IRWXG | S_IRWXO)) == -1) // If file exists
        {   
            // Abort
            perror("Error creating destination file");
            exit(EXIT_FAILURE);
        }

        // Read from the pipe
        ssize_t n;
        char writeBuffer[BUF_SIZE];
        while ((n = read(fd[READ_END], writeBuffer, BUF_SIZE)) > 0) 
        {
            // Write to the destination file
            if (write(outFd, writeBuffer, n) != n)
            {
                perror("Error writting to the destination file");    
                exit(EXIT_FAILURE);
            }
        }

        // Close the destination file
        close(outFd);

        // Close the write end of the pipe
        close(fd[READ_END]);

    } else                  // Parent process
    {   
        // Close the unused end of the pipe
        close(fd[READ_END]);

        // Open the input file
        int inFd;
        if ((inFd = open(argv[1], O_RDONLY)) == -1)  // If file doesn't exist
        {   
            // Abort
            perror("Error opening source file");    
            exit(EXIT_FAILURE);
        }
        
        // Read from the file
        ssize_t n;
        char readBuffer[BUF_SIZE];
        while ((n = read(inFd, readBuffer, BUF_SIZE)) > 0) 
        {
            // Write to the pipe
            if (write(fd[WRITE_END], readBuffer, n) != n)
            {
                perror("Error writting to the pipe");    
                exit(EXIT_FAILURE);
            }
        }

        // Close the source file
        close(inFd);

        // Close the read end of the pipe
        close(fd[WRITE_END]);
    }
    
    exit(EXIT_SUCCESS); // Terminate normally
}