/*
 *  Chap4.21/src/main.c
 *
 *  Programming Problem Chap. 4.21
 *  
 *  108590050 李浩銘
 * 
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define BUF_SIZE 65536

pthread_mutex_t mutex;

int fib[BUF_SIZE];

void usage(char *programName)
{
    printf("Usage:\n\t%s <num>\n", programName);
}

void* child(void* n)
{   
    int num = *(int*)n; // warp void* to int

    if (num < 0) exit(EXIT_FAILURE);

    // Using dynamic programming instead of recursion
    // Since an array for saving the fibo result is required anyway

    // mutex lock for thread scalability
    pthread_mutex_lock(&mutex);
    fib[0] = 0;
    fib[1] = 1;
    pthread_mutex_unlock(&mutex);
    
    for (int i=2; i<=num; ++i)
    {   
        // mutex lock for thread scalability
        pthread_mutex_lock(&mutex);
        fib[i] = fib[i-1] + fib[i-2];
        pthread_mutex_unlock(&mutex);
    }
    
    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    if (argc == 2 && !(strcmp(argv[1], "-h") && strcmp(argv[1], "--help")))
    {
        usage(argv[0]);
        exit(EXIT_SUCCESS);
    }

    int num; 
    if (argc == 2)
        num = atoi(argv[1]);

    else
    {
        printf("Input a positive integer: ");
        scanf("%d", &num);
    }

    if (num < 1)
    {
        printf("Please input a positive integer.\n");   // Error checking
        exit(EXIT_FAILURE);
    }
    num--;

    pthread_t tid;

    pthread_mutex_init(&mutex, 0);
    pthread_create(&tid, NULL, child, &num);    // Creatre child thread
    pthread_join(tid, NULL);                    // Wait for child thread finish
    pthread_mutex_destroy(&mutex);
    
    // output the sequence generated by the child thread.
    for (int i=0; i<num; ++i)
        printf("%d, ", fib[i]);
    printf("%d\n", fib[num]);

    exit(EXIT_SUCCESS);
}