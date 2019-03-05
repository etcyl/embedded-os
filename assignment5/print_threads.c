/*
Matt Fleetwood
3/4/2019
Portland, OR
Assignment 5 for ECE 362

Makes 4 threads and prints their IDs out.
Feel inspired.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Number of threads you'd really really like to have right meow
#define NUM_THREADS 4

//Print a thread's ID in a separate thread, because we can
void *print_thread_ID(void *vargp)
{
    int thread_ID = (int) vargp;
    printf("Will thread ID %d please move their white Tahoe in the parking lot\n", thread_ID);
    return;
}

int main()
{
    int loop_counter = 0;
    pthread_t some_threads[NUM_THREADS];
    for(loop_counter = 0; loop_counter < NUM_THREADS; ++loop_counter)
       {
          pthread_create(&(some_threads[loop_counter]), NULL, print_thread_ID, &(some_threads[loop_counter]));
          pthread_join(some_threads[loop_counter], NULL);
       }
    
    return 1;
}
