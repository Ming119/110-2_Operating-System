#include <stdlib.h>
#include "queue.h"

QNode* newNode(int k)
{
    QNode* node = malloc(sizeof(QNode));

    node->key = k;
    node->prev = node->next = NULL;

    return node;
}
 
Queue* createQueue(int numOfFrames)
{
    Queue* queue = malloc(sizeof(Queue));

    queue->capacity = numOfFrames;
    queue->count = 0;
    queue->front = queue->rear = NULL;
    
    return queue;
}

QNode* enqueue(Queue* queue, int key)
{   
    if (isQueueFull(queue)) return NULL;

    QNode* node = newNode(key);

    if (isQueueEmpty(queue)) {
        queue->front = queue->rear = node;
    } else {
        node->prev = queue->rear;
        queue->rear = queue->rear->next = node;
    }

    queue->count++;
    
    return node;
}

void dequeue(Queue* queue)
{
    if (isQueueEmpty(queue)) return;

    QNode* node = queue->front;
    queue->front = node->next;
    queue->front->prev = NULL;
    
    queue->count--;
    
    free(node);    
}

int isQueueFull(Queue *queue)
{
    return queue->count == queue->capacity;
}

int isQueueEmpty(Queue *queue)
{
    return queue->count == 0;
}