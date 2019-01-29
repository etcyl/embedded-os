/**
Matt Fleetwood
1/28/2019
Portland, OR
Assignment 2 for ECE 362

Accepts a filename (filename.txt) that includes a list of commads, one per line, to 
execute. Each command is executed by a subprocess (using fork and execvp). The output
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

int main(int argc, char *argv[]){
    int fd = open(argv[1], O_RDONLY); // Open the file using the second (1st) argument in argv
    int current_char = 0, char_count = 0, done = 0, i = 0, j = 0, k = 0; // Variables for reading the file
    char** BUFFER; // File buffer to store lines and chars read in; lines are commands to be done using 
                   // execvp
    // Check that the user entered a filename as argv[1] through the cmdline (as "filename.txt")
    if(argc != 2)  {
       write(STDERR_FILENO, "ERROR: expecting filename argument (filename.txt).\n", 51);
       return -1;
    }

    // Allocate memory for the file buffer
    BUFFER = (char**) malloc(sizeof(char*)*CIRC_BUFF_LEN);
    for(i = 0; i < BUFF_LEN; ++i)
        BUFFER[i] = (char*) malloc(sizeof(char)*CIRC_BUFF_LEN);
    i = 0;

    if(fd < 0)  { // File does not exist
        write(STDERR_FILENO, "ERROR: filename does not exist.\n", 31);
        return -1;
    }

    // File exists, read it into the file buffer
    while(!done)  {
        if(current_char = read(fd, BUFFER[i], RD_LEN) != 0) { // Check if we can read from the file
          // printf("Message\n"); i += 1; 
            done = 0; // If here, then not done yet (i.e. not at the end of the file)
            write(STDOUT_FILENO, BUFFER[i], RD_LEN);
        }
        else
            done = 1;
        
       // write(STDOUT_FILENO, BUFFER[i], RD_LEN); //printf("Read in: %s\n", BUFFER[i]);
    }
    close(fd);
   
    int rc = fork();
    if (rc < 0) { // fork failed; exit
       fprintf(stderr, "fork failed\n");
       exit(1);
    } else if (rc == 0) { // child: redirect STD_OUTPUT to a file
        close(STDOUT_FILENO);
        open("./capture", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
        char *myargs[3];
        if(strcmp(BUFFER[i], "wc\n") == 0)
           myargs[0] = strdup("wc");
        else if(strcmp(BUFFER[i], "ls\n") == 0)
           myargs[0] = strdup("ls");
        else
           myargs[0] = strdup("ls -l");
       // else
         // margs[0] = strdup("wc");
        // now exec "wc"...
        //char *myargs[2];//[3];
        //myargs[0] = strdup(BUFFER[0]);//"cat");//("wc"); //program: "wc" (word count)
        myargs[1] = strdup(BUFFER[0]); // Base-case [0] assumes 1 command, "ls" //"p4.c"); //argument: file to count
        myargs[2] = NULL; // marks end of array
        execvp(myargs[0], myargs); //runs word count   
    } else { // parent goes down this path (main)
        int rc_wait = wait(NULL);
    }
    return 0;
}
