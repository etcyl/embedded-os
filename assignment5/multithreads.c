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
int global_counter = 0;
int the_array[NUM_ARRAY_ELEMENTS];

//Function to use bubble sort as a thread on a quarter partition of the array
void *bubble_sort_thread(void *vargp)
{  
   int NUM = (int) vargp; //Determine which partition we should handle
   int x = 0, y = 0;
   int temp = 0; 

   for(x = 0; x < (NUM -1); x++)
      {
       for(y = 0; y < (NUM - x - 1); y++)
          {
           {if(the_array[y] > the_array[y+1])
             { 
               temp = the_array[y];
               the_array[y] = the_array[y+1];
               the_array[y+1] = temp;
             }
           }
          } 
       }
  
    return;
}

//Function to merge two partitions
void *merge_partitions(void *vargp)
{
    int CASE = (int) vargp; //Determine which two partitions we are merging
    int temp[sizeof(the_array) / 4], i = 0; 

    if(CASE == 0) //First case to merge first and second partitions
      {
       if(the_array[0] > the_array[sizeof(the_array) / 4])
          return;
       else
         {
          for(i = 0; i < sizeof(the_array) / 4; ++i)
          {   
              temp[i] = the_array[i];
              the_array[i] = the_array[i + sizeof(the_array) / 4];
              the_array[i + sizeof(the_array) / 4] = temp[i]; 
          }
         }
      }
    else if(CASE == 1) //Second case to merge third and fourth partitions
      {
        if(the_array[(sizeof(the_array) / 4)*2] > the_array[((sizeof(the_array) / 4) *3)])
          return;
        else
          {
          for(i = 0; i < sizeof(the_array) / 4; ++i)
           {
             temp[i] = the_array[(sizeof(the_array) / 4)*2];
             the_array[(sizeof(the_array) / 4)*2] = the_array[((sizeof(the_array) /4) *3)];
             the_array[((sizeof(the_array) / 4)*3)] = temp[i];
           }
          }
      }
    else // Default case to merge the last two partitions
      {
        printf("nothing yet");
      }
    return;
}

int main()
{   
    int loop_counter = 0, i = 0, num_length = NUM_ARRAY_ELEMENTS / 4;
    int copy = num_length;
    num_length = 0; 
    pthread_t tid;
 
    srand(time(NULL));
    for(i = 0; i < NUM_ARRAY_ELEMENTS; ++i){
       the_array[i] = rand() % 51;
       printf("init: %d\n", the_array[i]);
    }

    // Make NUM_THREADS number of threads
    for(loop_counter = 0; loop_counter < NUM_THREADS; loop_counter++)
       {
        pthread_create(&tid, NULL, bubble_sort_thread, num_length);
        ++global_counter;
        num_length = num_length + copy;
       }
   
    for(loop_counter = 0; loop_counter < NUM_THREADS; loop_counter++)
        pthread_join(&tid, NULL);

    pthread_create(&tid, NULL, merge_partitions, 0);
    pthread_create(&tid, NULL, merge_partitions, 1);
    pthread_create(&tid, NULL, merge_partitions, 2);

    for(i = 0; i < NUM_ARRAY_ELEMENTS; ++i)
       printf("new new: %d\n", the_array[i]);
    pthread_exit(NULL);

    return 0;
}
