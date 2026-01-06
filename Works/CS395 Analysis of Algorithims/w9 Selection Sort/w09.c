/*********************************************
 * Id: vill9577
 *
 * w09.c
 * February 25, 2021
 *
 * Program Description:
 *   Selection Sort
 *********************************************/

#include <stdio.h>
#include <stdlib.h>

//  Prints Array
void printArray(int A[], int size);

//  Sorts an Array of Integers Using Selection Sort
void SS(int A[], int size);

int main(int argc, char *argv[])
{
   // End program if the command line does not have at least 2 arguments
   if(argc < 2)
   {
      printf(">  Error: INVALID INPUT\n\n");
      printf("   Please enter at least 2 command line arguments when executing\n");
      printf("      E.g. \" %s 1 3 4 2 \"\n\n", argv[0]);
      printf("   Exiting Program ...\n");
      return 1;
   }

   int i;
   int size = argc - 1;
   int A[size];
   for(i = 0; i < size; i++)
   {
      A[i] = atoi(argv[i + 1]);
   }

   /* ALGORITHM HERE */
   SS(A, size);
   
   return 0;
}

//  Prints Array
void printArray(int A[], int size)
{
   int i;
   for(i = 0; i < size; i++)
   {
      printf("%d ", A[i]);
   }
   printf("\n");
}

//  Sorts an Array of Integers Using Selection Sort
void SS(int A[], int size)
{
   int i, j, min, temp;
   printArray(A, size);

   //for(i = 0; i < (size - 2); i++)
   for(i = 0; i < (size - 1); i++)               // CHANGED
    {
      min = i;
      //for(j = (i + 1); j < (size - 1); j++)
      for(j = (i + 1); j < size; j++)            // CHANGED
      {
         if(A[j] < A[min])
            min = j;
      }
      temp = A[i];
      A[i] = A[min];
      A[min] = temp;
      printArray(A, size);
   }
}
