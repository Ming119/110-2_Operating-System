/*
 *  Chap6Project3/src/main.c  
 *
 *  Programming Project Chap.6 Project 3
 *  Producer-Consumer Problem
 * 
 *  108590004 謝宗麟
 *  108590029 朱欣雨
 *  108590049 符芷琪
 *  108590050 李浩銘
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#include "buffer.h"

pthread_mutex_t mutex;
sem_t empty;

void usage(char *programName)
{
    printf("Usage:\n\t%s <sleeping time before terminating> <num of producer threads> <num of consumer threads>\n", programName);
}

void *producer(void *args) {
    int id = (int)args;
    buffer_item item;

    while (1) {
        /* sleep for a random period of time */
        sleep(rand() % BUFFER_SIZE);

        /* generate a randim number */
        item = rand();
        if (insert_item(item))
            perror("Insert Item");
        else
            printf("Producer %d produced %d\n", id, item);
    }
}

void *consumer(void * args) {
    int id = (int)args;
    buffer_item item;

    while (1) {
        /* sleep for a random period of time */
        sleep(rand() % BUFFER_SIZE);

        if (remove_item(&item))
            perror("Remove Item");
        else
            printf("Consumer %d consumed %d\n", id, item);
    }
}

int main(int argc, char *argv[])
{
    /* 1. Get command line arguments argv[1],argv[2],argv[3] */
    if ((argc > 1 && !(strcmp(argv[1], "-h") && strcmp(argv[1], "--help"))) || argc != 4)
    {
        usage(argv[0]);
        exit(EXIT_SUCCESS);
    }

    int sleepTime   = atoi(argv[1]);
    int numProducer = atoi(argv[2]);
    int numConsumer = atoi(argv[3]);

    if (sleepTime < 1 || numProducer < 1 || numConsumer < 1) {
        exit(EXIT_FAILURE);
    }

    /* 2. Initialize buffer */
    initBuffer();

    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    /* 3. Create producer thread(s) */
    pthread_t *tProducer = malloc(numProducer * sizeof(pthread_t));
    for (int i=0; i<numProducer; ++i)
        pthread_create(&tProducer[i], NULL, producer, (void*)(i+1));

    /* 4. Create consumer thread(s) */
    pthread_t *tConsumer = malloc(numConsumer * sizeof(pthread_t));
    for (int i=0; i<numConsumer; ++i)
        pthread_create(&tConsumer[i], NULL, consumer, (void*)(i+1));

    /* 5. Sleep */
    sleep(sleepTime);
    
    for (int i=0; i<numProducer; ++i)
        pthread_cancel(tProducer[i]);
    
    for (int i=0; i<numConsumer; ++i)
        pthread_cancel(tConsumer[i]);
        
    /* 6. Exit */
    free(tProducer);
    free(tConsumer);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    exit(EXIT_SUCCESS);
}
