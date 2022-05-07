/*
 *  Chap7.17/src/main.c
 *
 *  Programming Problem Chap. 4.17
 *  
 *  108590050 李浩銘
 * 
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define NUM_THREAD 16
#define MAX 3
#define NORTH 0
#define SOUTH 1

pthread_mutex_t mutex;
pthread_cond_t accessible[2];

int waiting[2];
int count = 0;
int turn;

void usage(char *programName)
{
    printf("Usage:\n\t%s\n", programName);
}

int isSafe(int direction)
{
    return (count == 0 || (direction == turn && count < MAX))? 1: 0;
}

void enterBridge(int direction) 
{
    pthread_mutex_lock(&mutex);

    while (!isSafe(direction))
    {
        waiting[direction]++;
        pthread_cond_wait(&accessible[direction], &mutex);
        waiting[direction]--;
    }

    count++;
    turn = direction;

    pthread_mutex_unlock(&mutex);
}

void exitBridge(int direction)
{
    pthread_mutex_lock(&mutex);

    if (--count == 0) {
        if (waiting[direction] > waiting[1-direction])
            pthread_cond_signal(&accessible[direction]);
        else
            pthread_cond_signal(&accessible[1-direction]);

    } else if (waiting[direction] > waiting[1-direction])
        pthread_cond_signal(&accessible[direction]);

    pthread_mutex_unlock(&mutex);
}

void* framer(void* args)
{
    int id = (int) args;
    int direction = rand() % 2;
    
    sleep(rand() % 2);
    printf("Framer %d want to enter the bridge from %s.\n", id, (direction)?"SOUTH":"NORTH");
    enterBridge(direction);
    printf("Framer %d is crossing the bridge.\n", id);
    sleep(rand() % 2);
    exitBridge(direction);
    printf("Framer %d exit the bridge.\n", id);
}

int main(int argc, char* argv[]) 
{
    if (argc == 2 && !(strcmp(argv[1], "-h") && strcmp(argv[1], "--help"))) {
        usage(argv[0]);
        exit(EXIT_SUCCESS);
    }

    srand(time(NULL));

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&accessible[0], NULL);
    pthread_cond_init(&accessible[1], NULL);

    pthread_t *tFramer = malloc(NUM_THREAD * sizeof(pthread_t));
    for (int i=0; i<NUM_THREAD; ++i)
        pthread_create(&tFramer[i], NULL, framer, (void*)(i+1));

    for (int i=0; i<NUM_THREAD; ++i)
        pthread_join(tFramer[i], NULL);
    
    pthread_cond_destroy(&accessible[0]);
    pthread_cond_destroy(&accessible[1]);
    pthread_mutex_destroy(&mutex);

    exit(EXIT_SUCCESS);
}