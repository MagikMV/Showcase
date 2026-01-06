#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char c = ' ';
    printf("Character: %cyaya\n", c);

/*
    int i;
    int z = 7;
    for(i = 0; i < z; i = i++)
    {
        printf("yaya%d\n", i); 
	i = i + 2;
    }
*/
/*
    char *newLine = "\"\n\"";
    char *litvalue;
    strncpy(litvalue, newLine, strlen(newLine));
    printf("String: %s\n", newLine);
    printf("Length: %d\n", strlen(newLine));
    printf("String: %s\n", litvalue);
    printf("Length: %d\n", strlen(litvalue));
    int count = 1;
    char *test = (char *) malloc(sizeof(char) * count);
    test[0] = 't';
    count++;
    test = (char *) realloc(test, sizeof(char) * count);
    test[1] = 'e';
    count++;
    test = (char *) realloc(test, sizeof(char) * count);
    test[2] = 's';
    count++;
    test = (char *) realloc(test, sizeof(char) * count);
    test[3] = 't';
    count++;
    test = (char *) realloc(test, sizeof(char) * count);
    test[4] = 'i';
    count++;
    test = (char *) realloc(test, sizeof(char) * count);
    test[5] = 'n';
    count++;
    test = (char *) realloc(test, sizeof(char) * count);
    test[6] = 'g';
    count++;
    test = (char *) realloc(test, sizeof(char) * count);
    test[7] = '\n';
    printf("Test: %s\n", test);
    printf("Count: %d\n", count);
    printf("Length: %d\n", strlen(test));
    printf("Size: %d\n", sizeof(test));
*/
    return 0;
}
