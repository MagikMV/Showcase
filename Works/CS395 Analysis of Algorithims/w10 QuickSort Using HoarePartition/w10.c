/*********************************************
 * Id: vill9577
 *
 * w10.c
 * April 8, 2021
 *
 * Program Description:
 *   QuickSort Using HoarePartition
 *********************************************/

#include <stdio.h>
#include <stdlib.h>

// Partitions array by Hoare's algorithm
int HoarePartition(int A[], int leftIndex, int rightIndex);

// Sorts arry using quicksort
void QuickSort(int A[], int size, int leftIndex, int rightIndex);

// Prints array
void printArray(int A[], int size, int leftIndex, int rightIndex);

// Swaps elements in array
void swap(int A[], int i, int j);

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
   QuickSort(A, size, 0, size - 1);
   printArray(A, size, 0, size - 1);

   return 0;
}

// Partitions array by Hoare's algorithm
int HoarePartition(int A[], int leftIndex, int rightIndex)
{
   int pivot = A[leftIndex];
   int i = leftIndex;		// "do while" increments 'i' before action 
   int j = rightIndex + 1;	// "do while" decrements 'j' before action

   do
   {
      // Find left most element greater than or equal to pivot
      do i++; while(A[i] < pivot);

      // Find right most element less than or equal to pivot
      do j--; while(A[j] > pivot);

      swap(A, i, j);

   } while(i <= j);

   // Undo last swap when 'i' is greater than or equal to 'j'
   swap(A, i, j);

   // Swap left index and 'j'
   swap(A, leftIndex, j);

   return j;
}

// Sorts arry using quicksort
void QuickSort(int A[], int size, int leftIndex, int rightIndex)
{
   if(leftIndex < rightIndex)
   {
      int partition = HoarePartition(A, leftIndex, rightIndex);
      QuickSort(A, size, leftIndex, partition - 1);
      QuickSort(A, size, partition + 1, rightIndex);
      printArray(A, size, leftIndex, rightIndex);
   }
}

// Prints array
void printArray(int A[], int size, int leftIndex, int rightIndex)
{
   int i;
   for(i = 0; i < size; i++)
   {
      if(i == leftIndex)
      {
         printf("[");
      }
      printf("%d", A[i]);
      if(i == rightIndex)
      {
         printf("] ");
      }
      printf(" ");
   }
   printf("\n");
}

// Swaps elements in array
void swap(int A[], int i, int j)
{
   int temp = A[i];
   A[i] = A[j];
   A[j] = temp;
}
