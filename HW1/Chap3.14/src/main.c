/*
 *  Chap3.14/src/main.c
 *
 *  Programming Problem Chap. 3.14
 *
 *  108590050 李浩銘
 */

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void usage(char *programName)
{
    printf("Usage:\n\t%s <num>\n", programName);
}

void sequence(int n)
{   
    while (n != 1)
    {
        printf("%d, ", n);
        
        n = n%2? 3*n+1: n/2;
    }

    printf("%d\n", n);
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

    // Error checking
    if (num < 1)
    {
        printf("Please input a positive integer.\n");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid_t pid = fork();
    if (pid < 0)            // Error occurred
    {
        perror("Fork Error");
        exit(EXIT_FAILURE);

    } else if (pid == 0)    //Child process
    {
        sequence(num);

    } else                  // Parent process
    {
        wait(NULL);
    }

    exit(EXIT_SUCCESS);
}