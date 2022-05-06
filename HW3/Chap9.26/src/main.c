/*
 *  Chap8.25/src/main.c
 *
 *  Programming Problem Chap. 8.25
 *  
 *  108590050 李浩銘
 * 
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "queue.h"

#define REFSTR_SIZE 16

int frameSzie = 0;
unsigned refStr[REFSTR_SIZE];

void usage(char *programName)
{
    printf("Usage:\n\t%s\n", programName);
}

void showFrames(Queue* frames)
{
    QNode* node = frames->front;
    printf("NULL ");
    while(node != NULL) {
        printf("<-> %d ", node->key);
        node = node->next;
    }
    printf("<-> NULL\n");
}

QNode* search(Queue* frames, unsigned page)
{
    QNode* node = frames->front;

    while (node != NULL) {
        if (node->key == page) return node;
        node = node->next;
    }
    
    return NULL;
}

QNode* predict(int pages[], Queue* frames, int idx)
{
    QNode* node = frames->front;
    QNode* res = node;
    int max = idx;

    while (node != NULL) {
        int i = idx+1;
        for (; i<REFSTR_SIZE; ++i) {
            if (node->key == pages[i]) {
                if (i > max) {
                    max = i;
                    res = node;
                }
                break;
            }
        }
        if (i == REFSTR_SIZE) return node;

        node = node->next;
    }

    return res;
}

void fifo()
{   
    unsigned faultsCount = 0;
    Queue* pageFrames = createQueue(frameSzie);

    for (int i=0; i<REFSTR_SIZE; ++i) {
        if (!search(pageFrames, refStr[i])) {
            faultsCount++;
            if (isQueueFull(pageFrames)) dequeue(pageFrames);
            enqueue(pageFrames, refStr[i]);
        }

        showFrames(pageFrames);
    }

    printf("FIFO Total Page Faults: %u\n\n", faultsCount);
}

void lru()
{
    unsigned faultsCount = 0;
    Queue* pageFrames = createQueue(frameSzie);

    for (int i=0; i<REFSTR_SIZE; ++i) {
        QNode* node = search(pageFrames, refStr[i]);
        if (node == NULL)
        {
            faultsCount++;
            if (isQueueFull(pageFrames)) dequeue(pageFrames);
            enqueue(pageFrames, refStr[i]);
        }
        else if (node != pageFrames->rear)
        {
            node->next->prev = node->prev;
            if (node->prev)
                node->prev->next = node->next;
            else 
                pageFrames->front = node->next;

            node->prev = pageFrames->rear;
            node->next = NULL;

            pageFrames->rear = pageFrames->rear->next = node;
        }

        showFrames(pageFrames);
    }

    printf("LRU Total Page Faults: %u\n\n", faultsCount);
}

void optimal()
{
    unsigned faultsCount = 0;
    Queue* pageFrames = createQueue(frameSzie);

    for (int i=0; i<REFSTR_SIZE; ++i) {
        if (!search(pageFrames, refStr[i])) {
            faultsCount++;
            if (!isQueueFull(pageFrames)) {
                enqueue(pageFrames, refStr[i]);
            } else {
                QNode* node = predict(refStr, pageFrames, i);
                node->key = refStr[i];
            }
        }

        showFrames(pageFrames);
    }

    printf("Optimal Total Page Faults: %u\n\n", faultsCount);
}

void printRefStr()
{
    for (int i=0; i<REFSTR_SIZE; ++i)
        printf("%d ", refStr[i]);
    printf("\n");
}

int main(int argc, char* argv[])
{
    if (argc == 2 && !(strcmp(argv[1], "-h") && strcmp(argv[1], "--help"))) {
        usage(argv[0]);
        exit(EXIT_SUCCESS);
    }

    if (argc != 2) {
        printf("Input frame size: ");
        scanf("%d", &frameSzie);
    } else
        frameSzie = atoi(argv[1]);

    srand(time(NULL));

    for (int i=0; i<REFSTR_SIZE; ++i)
        refStr[i] = rand() % 10;

    printRefStr();
    fifo();

    printRefStr();
    lru();
    
    printRefStr();
    optimal();

    exit(EXIT_SUCCESS);
}