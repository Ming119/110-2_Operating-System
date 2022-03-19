/*
 *  Chap2.15/src/main.c
 *
 *  Programming Problem Chap. 2.15
 *  
 *  108590050 李浩銘
 * 
 */  

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef BUF_SIZE
#define BUF_SIZE 64
#endif

void usage(char *programName)
{
    printf("Usage:\n\t%s <src> <dest>\n", programName);
}

void fcopy(char *f1, char *f2)
{   
    // Open the input file
    int inFd;
    if ((inFd = open(f1, O_RDONLY)) == -1)  // If file doesn't exist
    {   
        // Abort
        perror("Error opening source file");    
        exit(EXIT_FAILURE);
    }

    // Create output file
    int outFd;
    if ((outFd = open(f2, O_EXCL | O_CREAT | O_WRONLY, S_IRWXU | S_IRWXG | S_IRWXO)) == -1) // If file exists
    {   
        // Abort
        perror("Error creating destination file");
        close(inFd);
        exit(EXIT_FAILURE);
    }

    // Loop
    ssize_t n;
    char buffer[BUF_SIZE];
    while ((n = read(inFd, buffer, BUF_SIZE)) > 0)  // Read from input file, until read fails
    {
        if (write(outFd, buffer, n) != n)           // Write to output file
        {
            perror("Error copying file");
            close(inFd);
            close(outFd);
            exit(EXIT_FAILURE);
        }
    }

    
    close(inFd);    // Close input file
    close(outFd);   // Close output file

    printf("Copy complete!\n");   // Write completion message to screen
}

int main(int argc, char *argv[])
{
    if (argc == 2 && !(strcmp(argv[1], "-h") && strcmp(argv[1], "--help")))
    {
        usage(argv[0]);
        exit(EXIT_SUCCESS);
    }
    
    if (argc == 3)
    {
        fcopy(argv[1], argv[2]);

    } else
    {
        char f1[BUF_SIZE], f2[BUF_SIZE];

        // Acquire input file name
        printf("Input a source file: ");    // Write prompt to screen
        scanf("%[^\n]%*c", f1);             // Accept input

        // Acquire output file name
        printf("Input a destination file: ");   // Write prompt to screen
        scanf("%[^\n]%*c", f2);                 // Accept input

        fcopy(f1, f2);
    }

    exit(EXIT_SUCCESS); // Terminate normally
}