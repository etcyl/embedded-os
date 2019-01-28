/**
Matt Fleetwood
1/19/2019
Portland, OR
Assignment 2 for ECE 362
Accepts a filename and an optional n integer as input to the program.
If the filename does not exist, an error message is printed to stdout.
If the filename exists and n is larger than 0 but less than 10, the 
last n lines from the file are displayed to stdout.
If n is less than 1 or greater than 9, an error is shown to stdout.
If file exists but n is not specified, then the last 5 lines of the
file are displayed to stdout.

**/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define RD_LEN 10 // Read this many chars from a file at a time
#define FILE_CHAR_LIMIT 8192
#define BUFF_LEN 256 // Number of characters for each line
#define CIRC_BUFF_LEN FILE_CHAR_LIMIT// Number of lines

int main(int argc, char* argv[])
{
        int fd = open(argv[1], O_RDONLY); // Get the filename
        int n;  // Get the value for n
	int current_char = 0, char_count = 0, done = 0, i = 0, j = 0, k = 0;
        char to_display[RD_LEN], buff[FILE_CHAR_LIMIT];        
        char** BUFFER;
        
        //Allocate memory for the file buffer
        BUFFER = (char**) malloc(sizeof(char*)*CIRC_BUFF_LEN);
        for(i = 0; i < BUFF_LEN; ++i)
          BUFFER[i] = (char*) malloc(sizeof(char)*CIRC_BUFF_LEN);
        i = 0;

        if(argc != 3)
          n = 5;
        else
          n = atoi(argv[2]);
        

        if(fd < 0){ // File does not exist
		write(STDERR_FILENO, "ERROR: filename does not exist.\n", 31);
                return -1;
	}         
	else if(n > 0 && n < 10){ // File exists, n is a valid number
                //Read the file into the file buffer to index lines easily
                while(!done)
                 {
                     if(current_char = read(fd, BUFFER[i], RD_LEN) != 0)
                      {
                        i += 1;
                        done = 0;
                      }
                     else
                      done = 1; 
                 }
                close(fd);           
		
                if(i <= n)
                  {    for(j = 0; j < i; ++j)
                        write(STDOUT_FILENO, BUFFER[j], RD_LEN);
                   }
                 else if(i > n)
                   {
                     if(n==1)
                       write(STDOUT_FILENO, BUFFER[i-1], RD_LEN);
                     else
                     {
                      j = i - n;
                    
                      for(k = 0; k < n; ++k)
                        write(STDOUT_FILENO, BUFFER[k+j], RD_LEN);
                     }
                   }
                  else
                   { //Default case
                  
                   }
	        return 0;
	}
        else if(n <= 0 || n >= 10){ // n is an invalid number
                write(STDERR_FILENO, "ERROR: n can only be 1 - 9.\n", 28);
                close(fd);
		return -1;
	}
        else{ // Default case
		write(STDERR_FILENO, "Default case reached. Terminating program...\n", 55);
		return -1;
	}

	return 0;
}
