// THIS IS THE FIXED VERSION OF THE CODE

/*
 * The following code has a race condition. Detect it using Valgrind/Helgrind (10 pts)
 * Origin : https://www.classes.cs.uchicago.edu/archive/2014/spring/12300-1/labs/lab4/
 */

// File: lab4/race.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 20

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;      // Init a mutex for the pthreads used in the code

long accum = 0;

void *square(void *param) {
    int x = *(int *)param;
    pthread_mutex_lock(&mutex);     // Lock the mutex before updating the shared variable
    accum += x * x;
    pthread_mutex_unlock(&mutex);   // Unlock the mutex after updating the shared variable
    //sleep(1);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int *params[NUM_THREADS];

    for (long t = 0; t < NUM_THREADS; t++) {
        params[t] = malloc(sizeof(int));
        *params[t] = t + 1;
        pthread_create(&threads[t], NULL, square, (void *)params[t]);
    }

    for (long t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
        free(params[t]);
    }

    printf("%ld\n", accum);
    pthread_exit(NULL);

    pthread_mutex_destroy(&mutex);      // Destroy the mutex after the threads have finished
}