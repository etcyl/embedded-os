/**
Matt Fleetwood
1/28/2019
Portland, OR
Assignment 2 for ECE 362

Accepts a filename (filename.txt) that includes a list of commads, one per line, to 
execute. Each command is executed by a subprocess (using fork and system calls). The output
of each subprocess is written to the file capture.txt.
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
#define NUM_ARGS 5

int main(int argc, char *argv[]){
    int fd = open(argv[1], O_RDONLY); // Open the file using the second (1st) argument in argv
    int count = 0, current_char = 0, char_count = 0, done = 0, a = 0, i = 0, j = 0, k = 0, num_flines = 0, bytes_in_line = 0, byte_count[FILE_CHAR_LIMIT], num_excvp_args = 0; // Variables for reading the file
    char** BUFFER; // File buffer to store lines and chars read in; lines are commands to be done using  execvp
    char buffer[RD_LEN+1];
    // Check that the user entered a filename as argv[1] through the cmdline (as "filename.txt")
    if(argc != 2)  {
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
    printf("j is: %d, num lines is %d\n", j, num_flines);
    while(j < num_flines) { // Execute num_flines subprocesses   
 
        int rc = fork();
        
        if (rc < 0) { // fork failed; exit
           fprintf(stderr, "fork failed\n");
           exit(1);
        } else if (rc == 0) { // child: redirect STD_OUTPUT to a file
          close(STDOUT_FILENO);
            if(j == 0) {// First subprocess to execute, so create the file
             fd = open("./TEST", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
            }
            else // j > 0 so this is not the first subprocess, append to existing file
             fd = open("./TEST", O_RDWR | O_APPEND);
            
            system(BUFFER[j]);
            close(fd);
        } 
          else { // parent goes down this path
          int rc_wait = wait(NULL);
         }
        j += 1;
     }
   
    return 0;
}
