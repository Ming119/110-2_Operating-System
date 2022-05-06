#ifndef QUEUE_H
#define QUEUE_H

typedef struct QNode {
    int key;
    struct QNode *prev, *next;
} QNode;

typedef struct Queue {
    int capacity;
    int count;
    QNode *front, *rear;
} Queue;

QNode* newNode(int);
Queue* createQueue(int);
QNode* enqueue(Queue*, int);
void dequeue(Queue*);
int isQueueFull(Queue*);
int isQueueEmpty(Queue*);

#endif