/** Does the same as print_threads.c but without arrays. **/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Number of threads we want 
#define NUM_THREADS 4

//Function to print the thread ID
void *print_thread_ID(void *vargp)
{
    int thread ID = (int) vargp:
    printf("My thread ID is %d\n:', thread_ID);
    return;
}

   int loop_counter = 0;
   for(loop_counter = 0; loop_counter < NUM_THREADS; ++loop_counter)
      {
        pthread_t thread1;
        pthread_create(&thread1, NULL, print_thread_ID, NULL);
        pthread_join(thread1, NULL);
      }
   return 1;
}
