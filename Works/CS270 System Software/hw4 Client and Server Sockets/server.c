/* server.c
 *
 * Miguel Villanueva
 * CS 270
 *
 * Modified code from Sockets Tutorial 
 *   @ http://www.linuxhowtos.org/C_C++/socket.htm
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_TOKEN 64
#define TOKEN_DELIM " \t\n\r"

int argsCount = 0;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

// parseBuffer
     // Parses the buffer recieved from the Client
char **parseBuffer(char *buffer)
{
    int size = MAX_TOKEN;
    char **args = malloc(size * sizeof(char*));
    int index = 0;
    char *token;
    
    token = strtok(buffer, TOKEN_DELIM);
    while(token != NULL)
    {
	argsCount++;
	args[index] = token;
	index++;

	token = strtok(NULL, TOKEN_DELIM);
    }
    args[index] = NULL;
    return args;
}

// calc
     // Calculates Client result
char *calc(char **args)
{
    int retval;
    char *str;
    char *result;
    result = malloc(sizeof(char) * 128);
    strcpy(result, "Result: ");

    if(strcmp(args[0], "+") == 0)
    {
	retval = atoi(args[1]) + atoi(args[2]);
	sprintf(str, "%d", retval);
	strcat(result, str);
	return result;
    }
    else if(strcmp(args[0], "-") == 0)
    {
        retval = atoi(args[1]) - atoi(args[2]);
        sprintf(str, "%d", retval);
        strcat(result, str);
        return result;
    }
    else if(strcmp(args[0], "*") == 0)
    {
        retval = atoi(args[1]) * atoi(args[2]);
        sprintf(str, "%d", retval);
        strcat(result, str);
        return result;
    }
    else if(strcmp(args[0], "/") == 0)
    {
        retval = atoi(args[1]) / atoi(args[2]);
        sprintf(str, "%d", retval);
        strcat(result, str);
        return result;
    }
    else if(strcmp(args[0], "%") == 0)
    {
        retval = atoi(args[1]) % atoi(args[2]);
        sprintf(str, "%d", retval);
        strcat(result, str);
        return result;
    }
    else
    {
	return "ERROR, usage: operator integer integer";
    }
}

int main(int argc, char *argv[])
{
    char **args;
    char *result;
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
       error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
                sizeof(serv_addr)) < 0) 
                error("ERROR on binding");
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, 
                (struct sockaddr *) &cli_addr, 
                &clilen);
    if (newsockfd < 0) 
         error("ERROR on accept");
    bzero(buffer,256);
    n = read(newsockfd,buffer,255);
    if (n < 0) error("ERROR reading from socket");
    printf("Request: %s\n",buffer);

    args = parseBuffer(buffer);
    if(argsCount != 3)
    {
	result = "ERROR, usage: operator integer integer";
    }
    else
    {
	result = calc(args);
    }
    n = write(newsockfd, result, strlen(result));
    if (n < 0) error("ERROR writing to socket");
    close(newsockfd);
    close(sockfd);
    return 0; 
}
