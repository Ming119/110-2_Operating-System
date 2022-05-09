/*
 *  Chap7Project/src/main.c  
 *
 *  Programming Project Chap.7 Project
 *  Banker's Algorithm
 * 
 *  108590004 謝宗麟
 *  108590029 朱欣雨
 *  108590049 符芷琪
 *  108590050 李浩銘
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

/* these may be any values >= 0 */
#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES numOfRes

int numOfRes;

/* the available amount of each resource */
int *available;

/* the maximum demand of each customer */
int *maximum[NUMBER_OF_CUSTOMERS];

/* the amount currently allocated to each customer */
int *allocation[NUMBER_OF_CUSTOMERS];

/* the remaining need of each customer */
int *need[NUMBER_OF_CUSTOMERS];

pthread_mutex_t mutex;
sem_t process;

typedef struct Q {
    int customer_num;
    struct Q* next;
} Q;

Q* head;
Q* rear;

Q* enQ(int customer_num)
{
    Q* newNode = malloc(sizeof(Q));
    newNode->customer_num = customer_num;

    if (rear == NULL)
        head = rear = newNode;
    else
        rear = rear->next = newNode;
    
    return newNode;
}

Q* deQ()
{
    Q* node = head;
    head = node->next;

    return node;
}

void printState()
{
    printf("           | Maximum | Allocation | Need | Available |\n");
    for (int i=0; i<NUMBER_OF_CUSTOMERS; ++i)
    {   
        printf("Customer %d | ", i);
        for (int j=0; j<NUMBER_OF_RESOURCES; ++j)
            printf("%d ", maximum[i][j]);
        printf("| ");
        for (int j=0; j<NUMBER_OF_RESOURCES; ++j)
            printf("%d ", allocation[i][j]);
        printf("| ");
        for (int j=0; j<NUMBER_OF_RESOURCES; ++j)
            printf("%d ", need[i][j]);
        printf("| ");
        for (int j=0; j<NUMBER_OF_RESOURCES; ++j)
            printf("%d ", available[j]);
        printf("|\n");
    }
    printf("\n");
}

int safetyAlgoright(int customer_num)
{
    /* Step 1: Initialize Work = Available and Finish[i] = false */

    int work[NUMBER_OF_RESOURCES];
    int finish[NUMBER_OF_CUSTOMERS];

    for (int i=0; i<NUMBER_OF_RESOURCES; ++i)
        work[i] = available[i];
    
    for (int i=0; i<NUMBER_OF_CUSTOMERS; ++i)
        finish[i] = 0;

    while (1)
    {
        /* Step 2: Find an index i such that both
                    Finish[i] == false
                    Need(i) <= work
        */

        int finishFlag = 1;
        
        for (int i=0; i<NUMBER_OF_CUSTOMERS; ++i)
        {
            if (finish[i]) continue;

            for (int j=0; j<NUMBER_OF_RESOURCES; j++)
                if (need[i][j] > work[j]) break;
            
            /* Step 3: 
                Work = Work + Allocation(i)
                Finish[i] = true
                Go to Step 2.    
            */

            finishFlag = 0;
            finish[i] = 1;
            for (int j=0; j<NUMBER_OF_RESOURCES; j++)
                work[j] += allocation[i][j];
        }

        /* If no such i exists, break the loop and go to step 4. */
        if (finishFlag) break;
    }

    /* Step 4: If Finish[i] == true for all i, then the system is in a safe state. */

    for (int i=0; i<NUMBER_OF_CUSTOMERS; ++i)
        if (!finish[i]) return 0;

    return 1;
}

int request_resources(int customer_num, int request[])
{
    printf("Customer %d requests for ", customer_num);
    for (int i=0; i<NUMBER_OF_RESOURCES; ++i)
        printf("%d ", request[i]);
    printf("\n");

    pthread_mutex_lock(&mutex);

    for (int i=0; i<NUMBER_OF_RESOURCES; ++i)
        if (request[i] > need[customer_num][i]) // The process has exceeded its maximum claim.
            exit(EXIT_FAILURE);
    
    for (int i=0; i<NUMBER_OF_RESOURCES; ++i) {
        if (request[i] > available[i])  // The resources are not available.
        {   
            pthread_mutex_unlock(&mutex);

            printf("\tRequest denied: Resources for the request of customer %d are not available.\n", customer_num);

            return -1;
        }
    }

    for (int i=0; i<NUMBER_OF_RESOURCES; ++i)
    {
        available[i] -= request[i];
        allocation[customer_num][i] += request[i];
        need[customer_num][i] -= request[i];
    }
    
    if (!safetyAlgoright(customer_num))
    {
        for (int i=0; i<NUMBER_OF_RESOURCES; ++i)
        {
            available[i] += request[i];
            allocation[customer_num][i] -= request[i];
            need[customer_num][i] += request[i];
        }

        pthread_mutex_unlock(&mutex);

        printf("\tRequest denied: Request of Customer %d is unsafe.\n", customer_num);

        return -1;
    }
    
    pthread_mutex_unlock(&mutex);

    printf("\tRequest approved: Request of Customer %d is safe.\n", customer_num);

    enQ(customer_num);

    return 0;
}

int release_resources(int customer_num, int release[])
{
    printf("Customer %d releases ", customer_num);
    for (int i=0; i<NUMBER_OF_RESOURCES; ++i)
        printf("%d ", allocation[customer_num][i]);
    printf("\n");

    pthread_mutex_lock(&mutex);

    for (int i=0; i<NUMBER_OF_RESOURCES; ++i)
    {   
        available[i] += release[i];
        allocation[customer_num][i] -= release[i];
    }

    pthread_mutex_unlock(&mutex);

    return 0;
}

void* customer(void* args)
{
    int customer_num = (int)(args);

    sleep(rand()%2);

    while (request_resources(customer_num, need[customer_num]))
        sem_wait(&process);

    sleep(rand()%2);

    release_resources(customer_num, allocation[customer_num]);

    sem_post(&process);
}

void usage(char *programName)
{
    printf("Usage:\n\t%s <resources...>\n", programName);
}

int main(int argc, char* argv[])
{
    if (argc == 2 && !(strcmp(argv[1], "-h") && strcmp(argv[1], "--help")) || argc < 2) {
        usage(argv[0]);
        exit(EXIT_SUCCESS);
    }

    srand(time(NULL));

    numOfRes = argc - 1;
    available = malloc(NUMBER_OF_RESOURCES * sizeof(int));
    for (int i=0; i<NUMBER_OF_CUSTOMERS; ++i)
    {
        maximum[i] = malloc(NUMBER_OF_RESOURCES * sizeof(int));
        allocation[i] = malloc(NUMBER_OF_RESOURCES * sizeof(int));
        need[i] = malloc(NUMBER_OF_RESOURCES * sizeof(int));
    }

    for (int i=0; i<NUMBER_OF_RESOURCES; ++i) {
        available[i] = atoi(argv[i+1]);

        for (int j=0; j<NUMBER_OF_CUSTOMERS; j++)
            need[j][i] = maximum[j][i] = rand()%(available[i]+1);
    }   

    printState();

    pthread_t *tCustomer = malloc(NUMBER_OF_CUSTOMERS * sizeof(pthread_t));

    pthread_mutex_init(&mutex, NULL);
    sem_init(&process, 0, 0);

    for (int i=0; i<NUMBER_OF_CUSTOMERS; ++i)
        pthread_create(&tCustomer[i], NULL, customer, (void*)(i));

    for (int i=0; i<NUMBER_OF_CUSTOMERS; ++i)
        pthread_join(tCustomer[i], NULL);

    sem_destroy(&process);
    pthread_mutex_destroy(&mutex);
    
    printf("\nBanker's Algorithm:\n\t");
    while (head)
    {
        Q* node = deQ();
        printf("Customer %d%s", node->customer_num, (head)? " -> ": "");
    }
    printf("\n");

    for (int i=0; i<NUMBER_OF_CUSTOMERS; ++i)
    {
        free(need[i]);
        free(allocation[i]);
        free(maximum[i]);
    }
    free(tCustomer);
    free(available);
    
    exit(EXIT_SUCCESS);
}
