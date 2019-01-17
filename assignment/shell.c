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
    	NOTE since there are only 5 buffers available, only !1 to !5 work (i.e. the last 5).
	2. exit:
    	terminate the program.
	3. history:
    	print the saved commands (could be less than 5).
	4. parse n:
    	tokenize input line number n. This input line shouldn't be stored in the buffer, but instead display each word (token) on a
    	separate line.
   	NOTE: only parse 1 to parse 5 worki (i.e. the last 5), since there are only 5 buffers required for this assignment.
**/

#define BUFF_LEN 256
#define CIRC_BUFF_LEN 6

char user_in[BUFF_LEN], EXIT_CMD[BUFF_LEN], PARSE_CMD[BUFF_LEN], HISTORY_CMD[BUFF_LEN], BANG_CMD[BUFF_LEN], INVAL_REF[BUFF_LEN], NONE[BUFF_LEN];

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
	int line_count = 1, is_done = 0, buff_index = 0, mod_user_in, i, j;
	char temp[3];
	char** BUFFER, head;

	//Allocate memory for the line buffer
	BUFFER = (char**) malloc(sizeof(char*)*CIRC_BUFF_LEN);    
	for(i = 0; i < BUFF_LEN; ++i)
    	BUFFER[i] = (char*) malloc(sizeof(char)*BUFF_LEN);

	//head = BUFFER;

	strcpy(EXIT_CMD, "exit\n");
	strcpy(PARSE_CMD, "parse \n");
	strcpy(BANG_CMD, "!\n");
	strcpy(HISTORY_CMD, "history\n");
	strcpy(INVAL_REF, "INVAL\n");
	strcpy(NONE, "SECRET\n");
    
	for(i = 0; i < CIRC_BUFF_LEN - 1; ++i)
   	strcpy(BUFFER[i], " ");
    
	while(!is_done)
     	{
      	if(buff_index == 5)
         	buff_index = 0;
     	 
      	printf("\n%d>>", line_count);
      	fgets(user_in, sizeof(user_in), stdin);
     	 
      	//Check if the user is done
      	if(strcmp(user_in, EXIT_CMD) == 0)
         	{
          	printf("exit cmd entered, terminating shell . . . \n");
          	is_done = 1;
          	return 0;
         	}
      	//Check if the user entered the history command
      	else if(strcmp(user_in, HISTORY_CMD) == 0)
       	{
        	history(line_count, BUFFER);
        	//strcpy(BUFFER[buff_index], user_in);
       	}
      	//Check if the user entered the bang command
      	else if(user_in[0] == BANG_CMD[0])
      	{
             	if( (int) user_in[1] - '0' > line_count || (int) user_in[1] - '0' <= 0)
                	printf("INVALID REFERENCE3\n");
              	else if(strcmp(BUFFER[(int) user_in[1] - '0'], NONE) == 0)
                	printf("INVALID REFERENCE4\n");
              	else
              	{
                	if((int) user_in[1] - '0' == 1)
                    	j = 0;
                	else if((int) user_in[1] - '0' == 2)
                    	j = 1;
                	else if((int) user_in[1] - '0' == 3)
                    	j = 2;
                	else if((int) user_in[1] - '0' == 4)
                    	j = 3;
                	else if((int) user_in[1] - '0' == 5)
                    	j = 4;
                	printf("%s\n", BUFFER[j]);
              	}
      	//strcpy(BUFFER[buff_index], user_in);
      	}
      	//Check if the user entered the parse command
      	if(user_in[0] == PARSE_CMD[0])
        	{
         	if(user_in[1] == PARSE_CMD[1])
           	{
            	if(user_in[2] == PARSE_CMD[2])
              	{
               	if(user_in[3] == PARSE_CMD[3])
                 	{
                  	if(user_in[4] == PARSE_CMD[4] & user_in[5] == PARSE_CMD[5])
                  	{
                    	if(isdigit(user_in[6]))
                    	{  
                        	if((int) user_in[6] - '0' > line_count || (int) user_in[6] - '0' <= 0 || (int) user_in[6] - '0' >= CIRC_BUFF_LEN)
                           	printf("Can't parse that, line doesn't exist");
                        	else if(strcmp(BUFFER[(int) user_in[6] - '0'], INVAL_REF) == 0)
                            	printf("ERROR: invalid reference to a PARSE_CMD (parse N cmds not stored in buffer)");
                        	//else if(strcmp(BUFFER[(int) user_in[6] - '0'], NONE) == 0)
                           	// printf("HERE");
                        	else
                          	{
                           	if((int) user_in[6] - '0' == 1)
                            	j = 0;
                           	else if((int) user_in[6] - '0' == 2)
                            	j = 1;
                           	else if((int) user_in[6] - '0' == 3)
                            	j = 2;
                           	else if((int) user_in[6] - '0' == 4)
                            	j = 3;
                           	else if((int) user_in[6] - '0' == 5)
                            	j = 4;
                           	for(i = 0; i < strlen(BUFFER[j]) - 1; ++i)
                           	{
                              	if(BUFFER[j][i] == ' ')
                               	printf("\n");
                              	else if(BUFFER[j][i] == 'S' & BUFFER[j][i + 1] == 'E')
                               	//printf(" ");
                               	break;
                              	else
                               	printf("%c", BUFFER[j][i]);
                           	}
                           	//strcpy(BUFFER[buff_index], INVAL_REF);
                          	}
                    	}
                    	else
                        	printf("I can only parse digits, sorry!\n");
                  	}
                 	}
              	}
           	}
        	}
      	else
        	strcpy(BUFFER[buff_index], user_in);

      	line_count += 1;
      	buff_index += 1;
      	//if(line_count > 5)
         	//BUFFER += 1;
     	}
	return 0;
}

int history(int line_count, char** BUFFER)
{
	int i = 0;
    
	if(line_count == 1)
    	printf("No history to print, try entering some cmds . . . \n");
	else
    	{
    	for(i = 0; i < CIRC_BUFF_LEN - 1; ++i)
        	{
        	if(strcmp(BUFFER[i], NONE) == 0 || strcmp(BUFFER[i], INVAL_REF) == 0)
            	printf("");
        	else
            	printf("%s", BUFFER[i]);
        	}
    	}
 return 1;
}
