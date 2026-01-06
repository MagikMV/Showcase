/*********************************************
 * Id: vill9577
 *
 * w11.c
 * April 9, 2021
 *
 * Program Description:
 *   Insertion Sort
 *********************************************/

#include <stdio.h>
#include <stdlib.h>

// Sorts array using insertion sort
void InsertionSort(int A[], int size);

// Prints array
void printArray(int A[], int size, int i);

int main(int argc, char *argv[])
{
   // End program if the command line does not have at least 3 arguments
   if(argc < 3)
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

   /* ALOGORITHM HERE */
   InsertionSort(A, size);

   return 0;
}

// Sorts array using insertion sort
void InsertionSort(int A[], int size)
{
   int i;

   printArray(A, size, 0);
   for(i = 1; i < size; i++)
   {
      int v = A[i];
      int j = i - 1;
      while(j >= 0 && A[j] > v)
      {
         A[j+1] = A[j];
         j--;
      }
      A[j+1] = v;
      printArray(A, size, i);
   }
}

// Prints array
void printArray(int A[], int size, int i)
{
   int j;
   for(j = 0; j < size; j++)
   {
      printf("%d ", A[j]);
      if(j == i)
      {
         printf("| ");
      }
   }
   printf("\n");
}
