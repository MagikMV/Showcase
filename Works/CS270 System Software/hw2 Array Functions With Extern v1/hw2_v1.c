/* hw2_v1.c
 *
 * Miguel Villanueva
 * CS 270
 */

#include <stdio.h>
#include "hw2_v1.h"

extern int A[];

// SumAvg
    // Finds sum and returns average of a given array
double SumAvg(int *sum, double *avg)
{
    int i;
    for(i = 0; i < 8; i++)
    {
	(*sum) = (*sum) + A[i];
    }
    (*avg) = (double)(*sum)/8;
    printf("Sum: %d\n", (*sum));
    printf("Average: %f\n", (*avg));
    
    return (*avg);
}  
    
// Min
    // Finds the minimum value in a given array
int Min(int *minimum)
{
    int i;

    (*minimum) = A[0];
    for(i = 1; i < 8; i++)
    {
	if(A[i] < (*minimum))
	{
	    (*minimum) = A[i];
	}
    }
    printf("Minimum: %d\n", (*minimum));
   
    return (*minimum);
}

// Max
    // Finds the maximum value in a given array
int Max(int *maximum)
{
    int i;

    (*maximum) = A[0];
    for(i = 1; i < 8; i++)
    {
        if(A[i] > (*maximum))
        {
            (*maximum) = A[i];
        }
    }
    printf("Maximum: %d\n", (*maximum));

    return (*maximum);
}
