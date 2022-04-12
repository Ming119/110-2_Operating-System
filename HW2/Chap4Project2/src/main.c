/*
 *  Chap4Project1/src/main.c  
 *
 *  Programming Project Chap.4 Project 2
 *  Multithreaded sorting application
 * 
 *  108590002 謝宗麟
 *  108590029 朱欣雨
 *  108590049 符芷琪
 *  108590050 李浩銘
 */

#define BUF_SIZE 16

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

typedef struct {
    int left;
    int mid;
    int right;
} params_t;

pthread_mutex_t mutex;

int arr[BUF_SIZE];

void usage(char *programName)
{
    printf("Usage:\n\t%s\n", programName);
}

void printArray(int arr[]) {
    for (int i=0; i<BUF_SIZE; ++i) {
        printf("%d ", arr[i]);
        if (!((i+1)%16)) printf("\n");
    }
}

void* merge(void* args)
{
    params_t *params = args;

    // Create leftArr ← arr[left...mid] and rightArr ← arr[mid+1...right]
    int leftSize = params->mid - params->left + 1;
    int rightSize = params->right - params->mid;
    int leftArr[leftSize], rightArr[rightSize];

    for (int i=0; i<leftSize; ++i)
        leftArr[i] = arr[params->left + i];

    for (int i=0; i<rightSize; ++i)
        rightArr[i] = arr[params->mid+1 + i];

    // Maintain current index of sub-arrays and main array
    int leftIdx = 0;                // Initial index of left subarray
    int rightIdx = 0;               // Initial index of right subarray
    int mergeIdx = params->left;    // Initial index of merge array

    // Until we reach either end of either leftArr or rightArr, pick larger among
    // elements leftArr and rightArr and place them in the correct position at arr[left...right]
    while (leftIdx < leftSize && rightIdx < rightSize)
    {
        if (leftArr[leftIdx] <= rightArr[rightIdx])
            arr[mergeIdx++] = leftArr[leftIdx++];
        else
            arr[mergeIdx++] = rightArr[rightIdx++];
    }

    // When we run out of elements in either leftArr or rightArr,
    // pick up the remaining elements and put in arr[left...right]
    while (leftIdx < leftSize)
        arr[mergeIdx++] = leftArr[leftIdx++];
    
    while (rightIdx < rightSize)
        arr[mergeIdx++] = rightArr[rightIdx++];

    pthread_exit(NULL);     // exit thread
}

void* mergeSort(void* args)
{
    params_t *params = args;

    if (params->left < params->right)
    {   
        // mid = (left+right)/2 (Avoiding overflow by right-1)
        int mid = (params->left + (params->right - 1)) / 2;

        params_t leftParams = {params->left, 0, mid};                 // left...mid       (mid is useless, so we put 0)
        params_t rightParams = {mid+1, 0, params->right};             // mid+1...right    (mid is useless, so we pu 0)
        params_t mergeParams = {params->left, mid, params->right};    // left...mid...right

        pthread_t tLeft, tRight, tMerge;
        pthread_create(&tLeft, NULL, mergeSort, &leftParams);   // Create a child thread for left sub-array
        pthread_create(&tRight, NULL, mergeSort, &rightParams); // Create a child thread for right sub-array
        pthread_join(tLeft, NULL);  // Wait for the child thread of left sub-array finish
        pthread_join(tRight, NULL); // Wait for the child thread of right sub-array finish

        pthread_mutex_lock(&mutex); // Lock the whole thread, protect the global arr[]
        
        /* Create a child thread for merging algorithm 
         * This can be done by `this` thread, but for satisfy the requirement of the question
         * We create a thread for it    */ 
        pthread_create(&tMerge, NULL, merge, &mergeParams); 
        pthread_join(tMerge, NULL);     // Wait the the child thread of merging algorithm

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

    // Generate a random array
    srand(time(NULL));
    for (int i=0; i<BUF_SIZE; ++i)
        arr[i] = rand() % (BUF_SIZE*BUF_SIZE);

    printf("Array before sort: \n");
    printArray(arr);

    pthread_t tid;
    params_t params = {0, BUF_SIZE/2-1, BUF_SIZE-1};

    // Create a child thread for sorting algorithm
    // Here, we use merge sort
    pthread_create(&tid, NULL, mergeSort, &params);  
    pthread_join(tid, NULL);    // Wait for the child thread finish
    pthread_mutex_destroy(&mutex);
    
    // Print out the sorted array
    printf("\nArray after sort: \n");
    printArray(arr);

    exit(EXIT_SUCCESS);
}