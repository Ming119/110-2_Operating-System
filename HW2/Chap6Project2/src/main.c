/*
 *  Chap6Project2/src/main.c  
 *
 *  Programming Project Chap.6 Project 2
 *  The Dining Philosophers Problem
 * 
 *  108590002 謝宗麟
 *  108590029 朱欣雨
 *  108590049 符芷琪
 *  108590050 李浩銘
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define LEFT  (philosopher_number + numPhilosophers - 1) % numPhilosophers
#define RIGHT (philosopher_number + 1) % numPhilosophers

int numPhilosophers;

pthread_mutex_t mutex;
pthread_cond_t *cond_var;

enum s {THINKING, HUNGRY, EATING} *state;

void usage(char *programName)
{
    printf("Usage:\n\t%s <num>\n", programName);
}

void test(int philosopher_number) {
    if (state[philosopher_number] == HUNGRY &&
        state[LEFT]  != EATING && 
        state[RIGHT] != EATING)
        {   
            printf("Pholosopher %d is EATING.\n", philosopher_number+1);
            state[philosopher_number] = EATING;
            sleep(rand() % numPhilosophers);
            pthread_cond_signal(&cond_var[philosopher_number]);
        }
}

void pickup_fork(int philosopher_number) {
    pthread_mutex_lock(&mutex);

    printf("Philosopher %d is HUNGRY. She is trying to pick up a fork.\n", philosopher_number+1);

    state[philosopher_number] = HUNGRY;
    test(philosopher_number);

    while (state[philosopher_number] != EATING)
        pthread_cond_wait(&cond_var[philosopher_number], &mutex);

    pthread_mutex_unlock(&mutex);
}

void return_fork(int philosopher_number) {
    pthread_mutex_lock(&mutex);

    printf("Philosopher %d put down her fork.\n", philosopher_number+1);

    state[philosopher_number] = THINKING;
    test(LEFT);
    test(RIGHT);

    pthread_mutex_unlock(&mutex);
}

void *diningPhilosopher(void *args) {
    int philosopher_number = (int)args;

    while (1) {
        printf("Philosopher %d is THINKING.\n", philosopher_number+1);
        sleep(rand() % numPhilosophers);
        pickup_fork(philosopher_number);
        return_fork(philosopher_number);
    }
}

int main(int argc, char *argv[]) {
    if (argc == 2 && !(strcmp(argv[1], "-h") && strcmp(argv[1], "--help")))
    {
        usage(argv[0]);
        exit(EXIT_SUCCESS);
    }

    if (argc == 2) {

        numPhilosophers = atoi(argv[1]);

    } else {

        printf("Input the number of philosophers (>=3): ");
        scanf("%d", &numPhilosophers);

    }

    if (numPhilosophers < 3)
    {
        printf("The number of philosophers is less than 3.\n");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    pthread_t tPhilosophers[numPhilosophers];
    
    cond_var = malloc(numPhilosophers * sizeof(pthread_cond_t));
    state = malloc(numPhilosophers * sizeof(enum s));

    pthread_mutex_init(&mutex, NULL);
    for (int i=0; i<numPhilosophers; ++i) {
        state[i] = THINKING;
        pthread_cond_init(&cond_var[i], NULL);
        pthread_create(&tPhilosophers[i], NULL, diningPhilosopher, (void*)i);
    }
    
    for (int i=0; i<numPhilosophers; ++i)
        pthread_join(tPhilosophers[i], NULL);

    for (int i=0; i<numPhilosophers; ++i)
        pthread_cond_destroy(&cond_var[i]);
    pthread_mutex_destroy(&mutex);

    free(cond_var);
    free(state);

    exit(EXIT_SUCCESS);
}
