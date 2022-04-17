/*
 *  Chap6Project3/src/buffer.c  
 *
 *  Programming Project Chap.6 Project 3
 *  Producer-Consumer Problem
 * 
 *  108590002 謝宗麟
 *  108590029 朱欣雨
 *  108590049 符芷琪
 *  108590050 李浩銘
 */

#include "buffer.h"

/* the buffer */
buffer_item buffer[BUFFER_SIZE];

int in = 0;
int out = 0;

int insert_item(buffer_item item) {
    /* insert item into buffer
        return 0 if successful, otherwise
        return 1 indicating an error condition */

    // sem_wait(&empty);
    // pthread_mutex_lock(&mutex);

    if (sem_wait(&empty)) return 1;
    if (pthread_mutex_lock(&mutex)) return 1;

    buffer[in++] = item;
    in %= BUFFER_SIZE;

    // pthread_mutex_unlock(&mutex);
    // sem_post(&full);

    if (pthread_mutex_unlock(&mutex)) return 1;
    if (sem_post(&full)) return 1;
    
    return 0;
}

int remove_item(buffer_item *item) {
    /* remove an object from buffer
       placing it in item
        return 0 if successful, otherwise
        return 1 indicating an error condition */

    // sem_wait(&full);
    // pthread_mutex_lock(&mutex);

    if (sem_wait(&full)) return 1;
    if (pthread_mutex_lock(&mutex)) return 1;

    *item = buffer[out++];
    out %= BUFFER_SIZE;
    
    // pthread_mutex_unlock(&mutex);
    // sem_post(&empty);

    if (pthread_mutex_unlock(&mutex)) return 1;
    if (sem_post(&empty)) return 1;

    return 0;
}

void initBuffer() {
    for (int i=0; i<BUFFER_SIZE; ++i)
        buffer[i] = 0;
}