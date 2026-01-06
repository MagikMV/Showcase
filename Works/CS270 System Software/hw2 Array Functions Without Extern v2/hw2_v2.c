/* hw2_v2.c
 *
 * Miguel Villanueva
 * CS 270
 */

#include <stdio.h>
#include "hw2_v2.h"

// SumAvg
    // Finds sum and returns average of a given array
double SumAvg(int A[], int size, int *sum, double *avg)
{
    int i;
    for(i = 0; i < size; i++)
    {
	(*sum) = (*sum) + A[i];
    }
    (*avg) = (double)(*sum)/size;
    printf("Sum: %d\n", (*sum));
    printf("Average: %f\n", (*avg));
    
    return (*avg);
}  
    
// Min
    // Finds the minimum value in a given array
int Min(int A[], int size, int *minimum)
{
    int i;

    (*minimum) = A[0];
    for(i = 1; i < size; i++)
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
int Max(int A[], int size, int *maximum)
{
    int i;

    (*maximum) = A[0];
    for(i = 1; i < size; i++)
    {
        if(A[i] > (*maximum))
        {
            (*maximum) = A[i];
        }
    }
    printf("Maximum: %d\n", (*maximum));

    return (*maximum);
}

