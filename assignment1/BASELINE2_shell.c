/**
Matt Fleetwood
1/14/2019
Portland, OR
Assignment 1 for ECE 362

Acts as a simple shell program for interacting with the user.
Reads commands from the user to determine what to do.
Commands available:
    1. !x: 
        repeat the (absolute) input line numbered x (but only if it is one of the saved commands -- there maybe less than 5). 
        In addition to storing a copy of the command, display the original input line or display an error message if the argument x is invalid.
        NOTE this does not work yet beyond !99.
    2. exit: 
        terminate the program.
    3. history: 
        print the saved commands (could be less than 5).
    4. parse n: 
        tokenize input line number n. This input line shouldn't be stored in the buffer, but instead display each word (token) on a 
        separate line.
**/

#define BUFF_LEN 256

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    int line_count = 1, is_done = 0, i;
    char user_in[BUFF_LEN], EXIT_CMD[BUFF_LEN], PARSE_CMD[BUFF_LEN], HISTORY_CMD[BUFF_LEN], BANG_CMD[BUFF_LEN], temp[3];
    char** BUFFER;

    //Allocate memory for the line buffer
    BUFFER = (char**) malloc(sizeof(char*)*BUFF_LEN);    
    for(i = 0; i < BUFF_LEN; ++i)
        BUFFER[i] = (char*) malloc(sizeof(char)*BUFF_LEN);

    strcpy(EXIT_CMD, "exit\n");
    strcpy(PARSE_CMD, "parse \n");
    strcpy(BANG_CMD, "!\n");
    strcpy(HISTORY_CMD, "history\n");
    
    while(!is_done)
         {
          printf("\n%d>>", line_count); 
          fgets(user_in, sizeof(user_in), stdin);
          if(strcmp(user_in, EXIT_CMD) == 0)
             {
              printf("exit cmd entered, terminating shell . . . \n");
              is_done = 1;
              return 0;
             }
          
          if(user_in[0] == PARSE_CMD[0])
            {
             if(user_in[1] == PARSE_CMD[1])
               {
                if(user_in[2] == PARSE_CMD[2])
                  {
                   if(user_in[3] == PARSE_CMD[3])
                     {
                      if(user_in[4] == PARSE_CMD[4] & user_in[5] == PARSE_CMD[5])
                        printf("parse cmd detected.\n");
                     }
                  }
               }
            }
          
          if(strcmp(user_in, HISTORY_CMD) == 0)
             {
              printf("history cmd entered, printing history . . . \n");
              if(line_count == 0)
                  printf("No history to print, try entering some cmds . . . \n");
              else
              {
                for(i = 0; i < line_count; ++i)
                {
                  printf("%s", BUFFER[i]);
                }
              }
             }
          
          if(user_in[0] == BANG_CMD[0])
          {  
             //printf("statement is %d", atoi(user_in));
             //printf("bang cmd entered, repeating cmd %d", user_in[1] - '0');
             if(isdigit(user_in[2]))
               {
                   for(i = 0; i < 2; ++i)
                      temp[i] = user_in[i +1];
                   i = atoi(temp);
                  //printf("bang cmd entered, repeating cmd %d%d\n", user_in[1] - '0', user_in[2] - '0');
                  printf("bang cmd entered, repeating cmd %d\n", i);
                  if( i > line_count)
                    //printf("JUST KIDDING you can't do that; %d%d is not a valid line number (...yet)\n", user_in[1] - '0', user_in[2] - '0');
                    printf("JUST KIDDING you can't do that; %d is not a valid line number (...yet)\n", i);
                  else
                    printf("%s\n", BUFFER[i]);
               }
              else
              {
                  printf("bang cmd entered, repeating cmd %d\n", user_in[1] - '0');
                  if( (int) user_in[1] - '0' > line_count)
                    printf("JUST KIDDING you can't do that; %d is not a valid line number (...yet)\n", user_in[1] - '0');
                  else
                    printf("%s\n", BUFFER[(int) user_in[1] - '0']);
              }
             //else
                 //printf("%s\n", BUFFER[i]);
          }
          
          strcpy(BUFFER[line_count], user_in);
          printf("Cmd was: %s\n", BUFFER[line_count]);
          line_count += 1;
         }
    return 0;
}
