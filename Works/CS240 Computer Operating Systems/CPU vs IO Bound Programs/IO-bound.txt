/* IO-bound.c 
 *
 * Miguel Villanueva
 * CS 240
 */

#include <stdio.h>
#include <time.h>

int main()
{
    clock_t start, end;
    double time_spent;    
    FILE *fp;

    start = clock();
    printf("Program started...\n");

    while( ((clock() - start) / CLOCKS_PER_SEC) < 10 )
    {
	fp = fopen("IO.txt", "a");
	fprintf(fp, "m\n");
        fclose(fp);
    }    

    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Time elapsed: %f seconds\n", time_spent);
    printf("Program finished\n");

    return 0;
}
