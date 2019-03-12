Matt Fleetwood
ECE 362
3/10/2019
HW 5

*****************************************************************************************************************************
NOTE: Parts of the programs used in part 2 were modified from the following source:
	  http://mathcs.pugetsound.edu/~dchiu/teaching/archive/CS475sp17/code/?file=threadSort.c
	  
	  originally authored by Dchiu.
	  
	  The differences between this program and the multithreads.c included here is that the previous program used only
	  2 partition and 1 merge threads. The sorting algorithm used in the previous program is also different
	  (Insertion Sort). The program needed to be modified such that several more partition structs were added. Finally, 
	  a simple routine to check the final array needed to be included to the original program, and timer code needed to
	  be verified in the new program.
*****************************************************************************************************************************

There are two directories in this folder that correspond to the following two parts of HW5:

1. A program that creates 4 threads and prints out the thread ID.
   To run this program, change directories to the 4_threads folder and enter the following:
   $cd 4_threads
   $make threads
   $./a.out
   
   The output should say something like:
   "My thread ID is 1
    My thread ID is 2
	My thread ID is 3
	My thread ID is 4"
	
2. A program that uses four bubble sort threads on a randomly initialized array of 64,000 integers.
   Two extra threads merge the four partitions of the smaller sorted arrays into two partitions.
   A final thread merges the last two partitions into one final sorted listed.
   If the sort was complete, a simple routine prints "Sort complete", otherwise an error message is printed.
   To run this program, change directories to the Multithread_sort folder and enter the following:
   $ cd ../Multithreaded_sort
   $ make multithreads
   $ ./a.out
   
   An optional timer function can be used to determine the elapsed time of the threaded bubble sort program
   as well as the single-threaded version (created typing $ make singlethread; $ ./a.out
   
   Some examples of the expected output for these programs (i.e. multithreads.c and singlethread.c) are shown in 
   the pictures contained within the Multithreaded_sort subdirectory.
   