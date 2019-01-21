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

#define RD_LEN 10 // Read this many chars from a file at a time
#define FILE_CHAR_LIMIT 8192 //Assume we won't have files larger than 8 KB

int main(int argc, char* argv[])
{
        int fd = open(argv[1], O_RDONLY); // Get the filename
        int n;  // int n = atoi(argv[2]); // Get the value for n
        int current_char = 0, char_count = 0, done = 0;
        char to_display[RD_LEN], buff[FILE_CHAR_LIMIT];        
        
        if(argc != 3)
          n = 5;
        else
          n = atoi(argv[2]);
        

        if(fd < 0){ // File does not exist
                write(2, "ERROR: filename does not exist.\n", 31);
                return -1;
        }         
        else if(n > 0 && n < 10){ // File exists, n is a valid number
                char_count = read(fd, buff, FILE_CHAR_LIMIT);
                if( char_count >1 )
                   char_count -= 1;
                close(fd);           
                fd = open(argv[1], O_RDONLY);
                if(char_count <= n)
                  {
                   while(!done)
                     { 
                        if( (current_char = read(fd, to_display, RD_LEN)) !=0)
                          done = 0;
                        else
                          done = 1;
                        current_char = write(1, to_display, current_char);
                     }
                close(fd);
                   }
                else if(char_count > n)
                   { 
                     lseek(fd, char_count - n, SEEK_CUR);
                     while(!done)
                      {
                        if( (current_char = read(fd, to_display, RD_LEN)) !=0)
                          done = 0;
                        else
                          done = 1;

                        current_char = write(1, to_display, current_char);
                      }
                   }
                 else
                   { //Default case
                     write(2, "Default case reached. Terminating program...\n", 55);
                     close(fd);
                     return -1;
                   }
                return 0;
        }
        else if(n <= 0 || n >= 10){ // n is an invalid number
                write(2, "ERROR: n can only be 1 - 9.\n", 28);
                close(fd);
                return -1;
        }
        else{ // Default case
                write(2, "Default case reached. Terminating program...\n", 55);
                return -1;
        }

    return 0;
}
