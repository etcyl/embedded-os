/* 
 * Originally modified from:
 *  Created on: Jan 22, 2016
 *      Author: dchiu
 * mathcs.pugetsound.edu/~dchiu/teaching/archive/CS475sp17sp17/code/?file=threadSort.c
 *
 * timer.c from Tom Schubert


   This program modifies the previous two programs to spawn 4 threads to evenly divide an array
   so that it can be bubble sorted. The array originally contains random integers.
   Onces each of the four threads bubble sort their portion of the array, two threads 
   combine the 4 sorted lists into 2 sorted lists. A final thread combines the last 2 
   sorted lists into 1 list. 

   The print function from timer.c can be used to determine how long the program took to run.

   A function checks whether the sort was successful, if true then prints the message:
   "Sort complete", otherwise then prints an error message.

 */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#define SIZE 64000

//shared globals
int unsorted[SIZE];
int sorted[SIZE];

//structures to hold function parameters for pthread calls
struct mergeParams {
    int begin;
    int mid;
    int end;
};

struct bubbleSortParams {
    int start;
    int end;
};

//function prototypes
void fillArray(int size);
void* merge(void *args);
void* bubbleSort(void *args);
void printArray(int *list, int size);
int sort_check();

struct timeval startTime, endTime;

/**
 * Main function
 */
int main() {
    int sec_diff, msec_diff;
    gettimeofday(&startTime, NULL);
    //fill the unsorted array
    fillArray(SIZE);
    //printArray(unsorted, SIZE);

    //define the indices of the first two sublists
    int start1 = 0,
        end1 = SIZE/4,
        start2 = end1+1,
        end2 = SIZE/2,
        start11 = end2+1,
        end11 = 3*(SIZE/4),
        start22 = end11+1,
        end22 = SIZE-1,
        check = 0;

    //4 sorting threads, and 3 merge threads
    pthread_t threads[7];

    //prepare sorting params and fire off sorting threads
    struct bubbleSortParams sArgs[4];
    sArgs[0].start = start1;
    sArgs[0].end = end22;
    pthread_create(&threads[0], NULL, bubbleSort, &sArgs[0]); //deal with first sublist

    //wait for sorting threads to terminate
    pthread_join(threads[0], NULL);

    //prepare params and fire off merging thread
    struct mergeParams mArgs[3];

    mArgs[3].begin = start1;
    mArgs[3].mid = end2;
    mArgs[3].end = end22;
    pthread_create(&threads[6], NULL, merge, &mArgs[3]);

    pthread_join(threads[6], NULL);
    //main thread prints out the sorted array
   // printArray(sorted, SIZE);
    printTimeDiff();
    if(check = sort_check())
      printf("Sort complete\n");
    else
      printf("Error sorting\n");

    return 0;
}

int sort_check()
{
     int i, flag=0;
     for(i = 0; i < SIZE; i++){
        //printf("%d ", sorted[i]);
        if(sorted[i] < sorted[i+1])
          //printf(" true\n");
          flag = 0;
        else
          flag = 1;
       }
     if(flag)
       return 1;
     else
       return 0;
}
/**
 * Fills unsorted array with random ints
 * @param size is the size of the array
 */
void fillArray(int size) {
    int i;
    srand(time(NULL));
    for (i=0; i<size; i++)
        unsorted[i] = rand() % 1000;
}

/**
 * Merges two sorted halves of the unsorted[] array into sorted[]
 *
 * @param begin index of first element in first sublist
 * @param mid index of the first element in the second sublist
 * @param end index of the last element in the second sublist
 */
void* merge(void *args) {
    //unpack parameters
    struct mergeParams *params = (struct mergeParams*) args;
    int begin = params->begin,
        mid = params->mid,
        end = params->end;


    int i = begin, j = mid, tpos = begin;

    while (i < mid && j <= end)
    {
        if (unsorted[i] < unsorted[j])
            sorted[tpos++] = unsorted[i++];
        else
            sorted[tpos++] = unsorted[j++];
    }

    //still elements left over in first list. copy over
    while (i < mid)
        sorted[tpos++] = unsorted[i++];

    //still elements left over in first list. copy over
    while (j <= end)
        sorted[tpos++] = unsorted[j++];
    return NULL;
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

/**
 * Bubble Sort
 *
 * @param index of the first element in unsorted sublist
 * @param index of the last element in unsorted sublist
 */

void* bubbleSort(void *args)
{
    struct bubbleSortParams *params = (struct bubbleSortParams*) args;
    int x, n = params -> end, temp, y;
    if(n == SIZE - 1)
       n = SIZE;
    for(x = 0; x < (n - 1); x++)
      {
       for(y = 0; y < n - x - 1; y++)
         {if(unsorted[y] > unsorted[y+1])
            {temp = unsorted[y];
             unsorted[y] = unsorted[y+1];
             unsorted[y+1] = temp;}
         }
       }
}
/*
 * Prints the given array
 */
void printArray(int *list, int size) {
    int i;
    for (i=0; i<size-1; i++)
        printf("%d, ", list[i]);
    printf("%d\n", list[i]);
}

printTimeDiff()
{
  int sec_diff, msec_diff;

     gettimeofday(&endTime, NULL);

     sec_diff = endTime.tv_sec - startTime.tv_sec;

     msec_diff = endTime.tv_usec - startTime.tv_usec;
     if (msec_diff < 0 ) { msec_diff += 1000000; sec_diff--;}

     printf("\ntime elapsed: \n\t%4d sec\n\t%4d usec\n", sec_diff, msec_diff);
}

