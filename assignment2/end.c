/**
Matt Fleetwood
1/28/2019
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
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

#define RD_LEN 10 // Read this many chars into the file buffer at a time
#define FILE_CHAR_LIMIT 8192 // Store this many lines and chars from the file
#define BUFF_LEN 256 // Number of chars for each line
#define CIRC_BUFF_LEN FILE_CHAR_LIMIT // Number of lines
#define N 5 // argv[2], unless the user gives us one

int main(int argc, char *argv[]){
    int fd = open(argv[1], O_RDONLY); // Open the file using the second (1st) argument in argv
    int count = 0, current_char = 0, char_count = 0, n = 0, done = 0, a = 0, i = 0, j = 0, k = 0, num_flines = 0, bytes_in_line = 0, byte_count[FILE_CHAR_LIMIT], num_excvp_args = 0; // Variables for reading the file
    char** BUFFER; // File buffer to store lines and chars read in; lines are commands to be done using  execvp
    char buffer[RD_LEN+1];
    // Check that the user entered a filename as argv[1] and (optionally) a number of lines to display as argv[2]
    if(argc == 2)
       n = N;
    else if(argc == 3){
       n = atoi(argv[2]);
       if(n <= 0 || n > 9) {
          write(STDERR_FILENO, "ERROR: n must be between 1 and 9.\n", 35);
          return -1;
       }   
    }
    else{
       write(STDERR_FILENO, "ERROR: expecting filename argument (filename.txt).\n", 51);
       return -1;
    }

    // Allocate memory for the file buffer
    BUFFER = (char**) malloc(sizeof(char*)*CIRC_BUFF_LEN);
    for(i = 0; i < BUFF_LEN; ++i)
        BUFFER[i] = (char*) malloc(sizeof(char)*BUFF_LEN);//*CIRC_BUFF_LEN);
    i = 0;

    if(fd < 0)  { // File does not exist
        write(STDERR_FILENO, "ERROR: filename does not exist.\n", 31);
        return -1;
    }

    // File exists, first count number of lines
    while(!done)  {
        if(read(fd, &BUFFER[0][0], 1) != 0) { // Check if we can read from the file 
            done = 0; // If here, then not done yet (i.e. not at the end of the file)
            if(BUFFER[0][0] == '\n' || BUFFER[0][0] == 0){ // Check if there's a newline in the current char
              num_flines += 1;
              byte_count[i] = bytes_in_line;      
              i += 1;        
              bytes_in_line = 0;
            }
        }
        else
            done = 1;
       bytes_in_line += 1;
    } 
    close(fd);
    j = 0;
    done = 0;

    k = i = 0;
    fd = open(argv[1], O_RDONLY); // Open to fill in the array 
    while(!done)  {
        if(read(fd, BUFFER[i], byte_count[i]) != 0) {
          i += 1;
          done = 0;
        } 
        else
          done = 1;
    }
    close(fd);
    
   i = j = k = 0;
  
   if(num_flines <= n){
     for(i = 0; i < n; ++i)
        write(STDOUT_FILENO, BUFFER[i], strlen(BUFFER[i]));   
   }
   else if(num_flines > n){
     if(n == 1)
        write(STDOUT_FILENO, BUFFER[num_flines - 1], strlen(BUFFER[num_flines - 1]));
     else{
     k = num_flines - n;
     for(j = k; k < num_flines; ++k)
        write(STDOUT_FILENO, BUFFER[k], strlen(BUFFER[k]));
     }
   }
     

   return 0;
}
