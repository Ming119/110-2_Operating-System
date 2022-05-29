/*
 *  Chap12.16/src/main.c
 *
 *  Programming Problem Chap. 12.16
 *  
 *  108590050 李浩銘
 * 
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CYLINDERS 5000
#define NUMBER_OF_REQUESTS 1000

int *requestQueue;

void usage(char *programName)
{
    printf("Usage:\n\t%s <init pos of disk head>\n", programName);
}

int compare(const void *a, const void*b)
{
    int ia = *((int*)a);
    int ib = *((int*)b);

    if (ia == ib) return 0;
    if (ia < ib) return -1;
    return 1;
}

void fcfs(unsigned pos)
{
    unsigned total = abs(requestQueue[0] - pos);

    for (int i=1; i<NUMBER_OF_REQUESTS; ++i)
        total += abs(requestQueue[i] - requestQueue[i-1]);

    printf("FCFS: %u\n", total);
}

void sstf(unsigned pos)
{   
    unsigned current_pos = pos;
    unsigned total = 0;

    int numberOfRequest = NUMBER_OF_REQUESTS;
    int *requestQueue_copy = malloc(NUMBER_OF_REQUESTS*sizeof(int));
    for (int i=0; i<NUMBER_OF_REQUESTS; ++i)
        requestQueue_copy[i] = requestQueue[i];

    while (numberOfRequest > 0) {
        int min = __INT32_MAX__;
        int minIndex = 0;
        for (int j=0; j<numberOfRequest; ++j) {
            int diff = abs(requestQueue_copy[j] - current_pos);
            if (diff < min) {
                min = diff;
                minIndex = j;
            }
        }

        total += min;
        current_pos = requestQueue_copy[minIndex];

        for (int i=minIndex; i<numberOfRequest; ++i)
            requestQueue_copy[i] = requestQueue_copy[i+1];
        numberOfRequest--;
    }
    
    printf("SSTF: %u\n", total);
}

void scan(unsigned pos)
{
    int *requestQueue_sort = malloc(NUMBER_OF_REQUESTS*sizeof(int));
    for (int i=0; i<NUMBER_OF_REQUESTS; ++i)
        requestQueue_sort[i] = requestQueue[i];
    
    qsort(requestQueue_sort, NUMBER_OF_REQUESTS, sizeof(int), compare);

    int posIndex = 0;
    for (; posIndex<NUMBER_OF_REQUESTS; ++posIndex)
        if (requestQueue_sort[posIndex] > pos) break;
    
    unsigned total = requestQueue_sort[posIndex] - pos;
    for (int i=posIndex+1; i<NUMBER_OF_REQUESTS; ++i)
        total += requestQueue_sort[i] - requestQueue_sort[i-1];

    total += (CYLINDERS-1) - requestQueue_sort[NUMBER_OF_REQUESTS-1];
    total += (CYLINDERS-1) - requestQueue_sort[posIndex-1];

    for (int i=posIndex-1; i>0; --i)
        total += requestQueue_sort[i] - requestQueue_sort[i-1];

    printf("SCAN: %u\n", total);
}

void cScan(unsigned pos)
{
    int *requestQueue_sort = malloc(NUMBER_OF_REQUESTS*sizeof(int));
    for (int i=0; i<NUMBER_OF_REQUESTS; ++i)
        requestQueue_sort[i] = requestQueue[i];
    
    qsort(requestQueue_sort, NUMBER_OF_REQUESTS, sizeof(int), compare);

    int posIndex = 0;
    for (; posIndex<NUMBER_OF_REQUESTS; ++posIndex)
        if (requestQueue_sort[posIndex] > pos) break;
    
    unsigned total = requestQueue_sort[posIndex] - pos;
    for (int i=posIndex+1; i<NUMBER_OF_REQUESTS; ++i)
        total += requestQueue_sort[i] - requestQueue_sort[i-1];
    
    total += (CYLINDERS-1) - requestQueue_sort[NUMBER_OF_REQUESTS-1];
    total += (CYLINDERS-1);
    total += requestQueue_sort[0];

    for (int i=1; i<posIndex; ++i)
        total += requestQueue_sort[i] - requestQueue_sort[i-1];

    printf("C-SCAN: %u\n", total);
}

int main(int argc, char *argv[])
{
    if (argc == 2 && !(strcmp(argv[1], "-h") && strcmp(argv[1], "--help")) || argc != 2) {
        usage(argv[0]);
        exit(EXIT_SUCCESS);
    }

    unsigned initDiskHeadPos = atoi(argv[1]);

    srand(time(NULL));

    requestQueue = malloc(NUMBER_OF_REQUESTS*sizeof(int));
    for (int i=0; i<NUMBER_OF_REQUESTS; ++i)
        requestQueue[i] = rand() % CYLINDERS;

    fcfs(initDiskHeadPos);
    sstf(initDiskHeadPos);
    scan(initDiskHeadPos);
    cScan(initDiskHeadPos);

    exit(EXIT_SUCCESS);
}