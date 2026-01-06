/* main.c    [hw 2.1]
 *
 * CS 270 Bolden
 * Miguel Villanueva  //  vill9577@vandals.uidaho.edu
 * March 1, 2020
 *
 * Program Description:
 * 	Generates an array of integers; finds the sum, average,  
 *      minimum value, and maximum value of the array.
 */

#include <stdio.h>
#include <stdlib.h>
#include "hw2_v1.h"

int A[8];

int main()
{
    int i, sum = 0;
    double j, avg;
    int minimum, maximum;

    printf("====================\n");
    printf("Array: ");
    for(i = 0; i < 8; i++)
    {
	A[i] = rand() % 20 + 1;
        printf("%d ", A[i]);
    }
    printf("\n\n");

    j = SumAvg(&sum, &avg);
    minimum = Min(&minimum);
    maximum = Max(&maximum);
    printf("====================\n");

    return 0;
}
