// THIS IS THE FIXED VERSION OF THE CODE
// Showing how the Guard and Singleton work

/*
 * The following code has a race condition. Detect it using Valgrind/Helgrind (10 pts)
 * Origin : https://www.classes.cs.uchicago.edu/archive/2014/spring/12300-1/labs/lab4/
 */

// File: lab4/race.c        ->      race.cpp
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "Guard.hpp"
#include "Singleton.hpp"

#define NUM_THREADS 20

long accum = 0;

std::mutex mutex;

void *square(void *param) {
    Guard guard(mutex);
    int x = *(int *)param;
    accum += x * x;
    //sleep(1);
    pthread_exit(NULL);
}

int main() {
    MySingleton *single = MySingleton::getInstance();
    single->displayMessage();

    MySingleton *single2 = MySingleton::getInstance();
    single2->displayMessage();

    std::cout << "Singletons are the same: " << (single == single2) << std::endl;

    pthread_t threads[NUM_THREADS];
    int *params[NUM_THREADS];

    for (long t = 0; t < NUM_THREADS; t++) {
        params[t] = (int *)malloc(sizeof(int));         // added her conversion to int pointer
        *params[t] = t + 1;
        pthread_create(&threads[t], NULL, square, (void *)params[t]);
    }

    for (long t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
        free(params[t]);
    }

    printf("%ld\n", accum);
    pthread_exit(NULL);
}