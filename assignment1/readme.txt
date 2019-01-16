ECE 362
1/17/2019
Matt Fleetwood
Assignment 1

      This program uses dynamically allocated arrays for a bash-like circular buffer.
      Acts as a simple shell program for interacting with the user.
      Reads commands from the user to determine what to do.
      As per the requirements of this assignment, there is "a function (or set of functions) to support
      a bash-like history capability." 
      Specifically, an int main() function handles running the entire program, history() shows the history of commands if they exist, and       several C standard library functions (e.g. atoi(), isdigit(), strcpy()) accomplish the various aspects of this program.
      That is, a main program or function accepts inputs from the user in order to accomplish the following commands:
        
        1. !x: 
        repeat the (absolute) input line numbered x (but only if it is one of the saved commands -- there maybe less than 5). 
        In addition to storing a copy of the command, display the original input line or display an error message if the argument x is i           invalid.
        NOTE this does not work yet beyond !99.
        
        2. exit: 
        terminate the program.
       
        3. history: 
        print the saved commands (could be less than 5).
        
        4. parse n: 
        tokenize input line number n. This input line shouldn't be stored in the buffer, but instead display each word (token) on a 
        separate line.

      To compile the program, type make all in the command line of the terminal.

      To run the program, type ./shell in the terminal.

      To delete the program, type make clean in the command line of the terminal.
