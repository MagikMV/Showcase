/* msh.c   [my shell]
 *
 * Miguel Villanueva
 * CS 240 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/* (PERSONAL NOTE) Functions/macros I learned 
   more about and their respective libraries
 
   <stdio.h>
	- getchar()
	- perror()
   <stdlib.h>
	- malloc(), free()
	- exit()
	- EXIT_SUCCESS, EXIT_FAILURE
	- execvp()
   <string.h>
	- strcmp()
	- strtok()
   <unistd.h>
	- fork(), exec()
	- pid_t 
   <sys/wait.h>
	- waitpid()
*/

#define MAX_STRING 512
#define MAX_TOKEN 64
#define TOKEN_DELIM " \t\n\r"

char *readLine(void);
char **parseLine(char *line);
int msh_exit(char **args);
int msh_launch(char **args);
int msh_execute(char **args);
void msh_loop(void);

int main()
{
    msh_loop();    
}

// readLine
    // Reads the command line one character at a time
char *readLine(void)
{
    int length = MAX_STRING;
    char *line = malloc(length * sizeof(char));
    int index = 0;

    int c;   //   'c' declared as int to check EOF

    while(1)
    {
	//  Read a character
	c = getchar();

	//  If EOF, replace with null character and return
	if(c == EOF || c == '\n')
	{
	    line[index] = '\0';
	    return line;
	}
	//  Else put character in string
	else
	{
	    line[index] = c;
	}

	//  Increment index
	index++;
    }
}

// parseLine
    // Parses the line read from the command line
char **parseLine(char *line)
{
    int size = MAX_TOKEN;
    char **args = malloc(size * sizeof(char*));
    int index = 0;
    char *token;

    if(!args)
    {
	fprintf(stderr, "msh: allocation error\n");
	exit(EXIT_FAILURE);
    }
    
    token = strtok(line, TOKEN_DELIM);
    while(token != NULL)
    {
	args[index] = token;
	index++;
	
	token = strtok(NULL, TOKEN_DELIM);
    }
    args[index] = NULL;
    return args;
}

// msh_exit
    // Built in shell function to exit
int msh_exit(char **args)
{
    return 0;
}

// msh_launch
    // Launches program and waits for termination
int msh_launch(char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if(pid == 0)
    {
	//  Child process
	if(execvp(args[0], args) == -1)
	{
	    perror("msh");
	}
	exit(EXIT_FAILURE);
    }
    else if(pid < 0)
    {
	//  Forking error
	perror("msh");
    }
    else
    {
	//  Parent process
	do
	{
	    wpid = waitpid(pid, &status, WUNTRACED);	   
	}while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

// msh_execute
    // Execute built in shell function(s) or launch program
int msh_execute(char **args)
{
    int i;

    if(args[0] == NULL)
    {
	// An empty command was entered
	return 1;
    }
    
    //  Built in exit function
    if(strcmp(args[0], "exit") == 0)
    {
	return msh_exit(args);
    }

    //  If no exit, then launch
    return msh_launch(args);
}

// msh_loop
    // Shell loop, recieves input and executes it
void msh_loop(void)
{
    char *line;
    char **args;
    int status;

    do
    {
	printf("?: ");
	line = readLine();
	args = parseLine(line);
	status = msh_execute(args);

	free(line);
	free(args);
    }while(status);
}
