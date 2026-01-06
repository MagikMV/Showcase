/* hw1.c
 *
 * CS 270 Bolden
 * Miguel Villanueva  //  vill9577@vandals.uidaho.edu
 * February 14, 2020
 *
 * Program Description:
 * 	Parses strings from the command line into
 *      tokens (or words)
 */

int makearg(char s[], char **args[]);
int lengthof(char s[]);

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i;
    int tc;           //  token count
    char **args;      //  parameter for makearg function
    char string[256]; 

    printf("Enter a string(6 words maximum): %s", string);
    scanf("%[^\n]", string);
    tc = makearg(string, &args);

    printf("Number of tokens: %d\n", tc);
    for(i = 0; i < tc; i++)
    {
	printf("Token %d: %s\n", i + 1, args[i]);
    }
    
    return 0;
}

int makearg(char s[], char **args[])
{
    int i, j;
    int count = 0;
    char **plsWork;     //  appropriately named - it worked (kinda)
    int size = lengthof(s);

    plsWork = malloc(32 *sizeof(char));
    for(j = 0; j < 32; j++)
    {
	plsWork[j] = malloc(32 * sizeof(char));
    } 

    for(i = 0; i < size; i++)
    {
	int k = 0;
	int index = 0;
	int tl = 0;      //  token length
	char token[32];
	while(s[i] != ' ' && s[i] != '\0')
	{
	    token[index] = s[i];
	    index++;
	    tl++;
            i++;
	}
	token[index] = '\0';   
              
/////////////////////////////////////////////////////////////////////
		/* BEWARE, CODING GRAVEYARD */
		/* THIS IS WHERE MANY IDEAS */
                /*           DIED           */
	
	//plsWork = malloc((count + 1) *sizeof(char));
	//plsWork[count] = malloc(tl * sizeof(char));

/////////////////////////////////////////////////////////////////////
	while(token[k] != '\0')
	{
	    plsWork[count][k] = token[k];
	    k++;
	}
        plsWork[count][k] = '\0'; 
	
	count++;
    }
    args[0] = plsWork;
    
    return count;
}

int lengthof(char s[])
{
    int i = 0;
    int length = 0;
    while(s[i] != '\0')
    {
	length++;
        i++;
    }
    
    return length;
}
