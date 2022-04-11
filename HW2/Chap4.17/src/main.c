/*
 *  Chap4.17/src/main.c
 *
 *  Programming Problem Chap. 4.17
 *  
 *  108590050 李浩銘
 * 
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t mutex;

int totalNumberOfPoints = 1000000;
int numberOfPointsInCircle = 0;

void usage(char *programName)
{
    printf("Usage:\n\t%s\n", programName);
}

double randDouble(double min, double max)
{
    // Ref: https://ubuntuforums.org/showthread.php?t=1717717&p=10618266#post10618266
    return min + (rand() * (max - min) / RAND_MAX);
}

double estimatePi()
{
    // pi = 4 * number of points in circle / total number of points
    return 4 * (double)(numberOfPointsInCircle) / (double)(totalNumberOfPoints);
}

void* child()
{
    for (int i=0; i<totalNumberOfPoints; ++i)
    {
        // Generate a random point as simple (x,y) coordinates.
        // The point must fall within the Cartesian coordinates that bound the square (-1, 1)
        double x = randDouble(-1, 1);
        double y = randDouble(-1, 1);

        // Distance between the generated point and the origin (0, 0) (using Pythagorean theorem)
        // Sicne the radius is 1, therefore no square root is required
        double dist = x*x + y*y;
        
        // Count the number of points that occur within the circle and store that result in a global variable.
        if (dist <= 1)  // Remember the radius is 1
        {   
            // mutex lock for thread scalability
            pthread_mutex_lock(&mutex);
            numberOfPointsInCircle++;
            pthread_mutex_unlock(&mutex);
        }
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

    srand(time(NULL));  // For rand()

    pthread_t tid;
    pthread_create(&tid, NULL, child, NULL);    // Create child thread
    pthread_join(tid, NULL);                    // Wait for child thread finish
    pthread_mutex_destroy(&mutex);
    
    // Calculate and output the estimated value of pi.
    double pi = estimatePi();
    printf("Estimated value of pi: %f\n", pi);

    exit(EXIT_SUCCESS);
}