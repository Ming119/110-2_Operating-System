/*
 *  Chap6Project3/src/buffer.h  
 *
 *  Programming Project Chap.6 Project 3
 *  Producer-Consumer Problem
 * 
 *  108590002 謝宗麟
 *  108590029 朱欣雨
 *  108590049 符芷琪
 *  108590050 李浩銘
 */

#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

typedef int buffer_item;

pthread_mutex_t mutex;
sem_t empty;
sem_t full;

int insert_item(buffer_item);
int remove_item(buffer_item*);
void initBuffer();