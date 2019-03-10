/*
Matt Fleetwood
3/4/2019
Portland, OR
Assignment 5 for ECE 362

Makes 4 threads and bubble sorts an array using each thread.
Feel inspired.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

//Number of threads we are having for dinner
#define NUM_THREADS 4
#define NUM_ARRAY_ELEMENTS 16
int g = 0, global_counter = 0;
int the_array[NUM_ARRAY_ELEMENTS];

//Function to print the thread ID
void *bubble_sort_thread(void *vargp)
{  
   int NUM = (int) vargp;
   int x = 0, y = 0;
   int temp = 0; 

   for(x = 0; x < (NUM -1); x++)
      {
       for(y = 0; y < (NUM - x - 1); y++)
          {
           {if(the_array[y] > the_array[y+1])
             { //printf("in the if");
               temp = the_array[y];
               the_array[y] = the_array[y+1];
               the_array[y+1] = temp;
             }
           }
          } 
       }
   /** int *myid = (int *)vargp;
    static int s = 0;
    ++s; ++g;
    printf("Thread ID: %d, Static: %d, Global: %d\n", *myid, ++s, ++g);
    **/
    return;
}

int main()
{   
    int loop_counter = 0, i = 0, num_length = NUM_ARRAY_ELEMENTS / 4;
    int copy = num_length;
    pthread_t tid;   
    
    srand(time(NULL));
    for(i = 0; i < NUM_ARRAY_ELEMENTS; ++i){
       the_array[i] = rand() % 13;
       printf("init: %d\n", the_array[i]);
    }

    // Make NUM_THREADS number of threads
    for(loop_counter = 0; loop_counter < NUM_THREADS; loop_counter++)
       {
        pthread_create(&tid, NULL, bubble_sort_thread, num_length);
        ++global_counter;
        num_length = num_length + copy;
       }
    
    // pthread_exit(NULL);

    for(i = 0; i < NUM_ARRAY_ELEMENTS; ++i)
       printf("new new: %d\n", the_array[i]);
    pthread_exit(NULL);

     return 0;
}
