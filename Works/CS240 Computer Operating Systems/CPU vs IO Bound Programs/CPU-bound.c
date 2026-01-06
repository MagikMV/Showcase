/* CPU-bound.c
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
    int count = 0;

    start = clock();
    printf("Program started...\n");

    while( ((clock() - start) / CLOCKS_PER_SEC) < 300 )
    {
	count = count + 1;
    }    

    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Time elapsed: %f seconds\n", time_spent);
    printf("Total count: %d seconds\n", count);
    printf("Program finished\n");

    return 0;
}
