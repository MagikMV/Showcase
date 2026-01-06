/*********************************************
 * Id: vill9577
 *
 * w12.c
 * April 16, 2021
 *
 * Program Description:
 *   Compare Sorts:
 *     - Selection
 *     - Insertion
 *     - Quicksort
 *********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

//  Sorts an Array of Integers Using Selection Sort
void SS(int A[], int size);

// Sorts array using insertion sort
void InsertionSort(int A[], int size);

// Sorts arry using quicksort
void QuickSort(int A[], int size, int leftIndex, int rightIndex);

// Partitions array by Hoare's algorithm
int HoarePartition(int A[], int leftIndex, int rightIndex);

// Swaps elements in array
void swap(int A[], int i, int j);

int main(int argc, char *argv[])
{
   int size1, size2, size3;
   size1 = 1000;
   size2 = 10000;
   size3 = 100000;

   int a1[size1];
   int a2[size2];
   int a3[size3];

   int i;
   srand(time(NULL));

   //  Fill arrays
   for(i = 0; i < size1; i++)
   {
      a1[i] = rand() % size1 + 1;
   }
   for(i = 0; i < size2; i++)
   {
      a2[i] = rand() % size2 + 1;
   }
   for(i = 0; i < size3; i++)
   {
      a3[i] = rand() % size3 + 1;
   }

   struct timeval start, stop;
   double time1, time2, time3;  // For Selection Sort
   double time4, time5, time6;  // For Insertion Sort
   double time7, time8, time9;  // For Quick Sort

   /* ALOGORITHMS HERE */
   // Super Inefficient But I Can Live With It
   // Would Have Done A Function Pointer But QuickSort Has More Parameters Than The Other Sorts
   gettimeofday(&start, NULL);
   SS(a1, size1);
   gettimeofday(&stop, NULL);
   time1 = (double)(stop.tv_sec - start.tv_sec) * 1000 + (double)(stop.tv_usec - start.tv_usec) / 1000;

   gettimeofday(&start, NULL);
   SS(a2, size2);
   gettimeofday(&stop, NULL);
   time2 = (double)(stop.tv_sec - start.tv_sec) * 1000 + (double)(stop.tv_usec - start.tv_usec) / 1000;

   gettimeofday(&start, NULL);
   SS(a3, size3);
   gettimeofday(&stop, NULL);
   time3 = (double)(stop.tv_sec - start.tv_sec) * 1000 + (double)(stop.tv_usec - start.tv_usec) / 1000;

   gettimeofday(&start, NULL);
   InsertionSort(a1, size1);
   gettimeofday(&stop, NULL);
   time4 = (double)(stop.tv_sec - start.tv_sec) * 1000 + (double)(stop.tv_usec - start.tv_usec) / 1000;

   gettimeofday(&start, NULL);
   InsertionSort(a2, size2);
   gettimeofday(&stop, NULL);
   time5 = (double)(stop.tv_sec - start.tv_sec) * 1000 + (double)(stop.tv_usec - start.tv_usec) / 1000;

   gettimeofday(&start, NULL);
   InsertionSort(a3, size3);
   gettimeofday(&stop, NULL);
   time6 = (double)(stop.tv_sec - start.tv_sec) * 1000 + (double)(stop.tv_usec - start.tv_usec) / 1000;

   gettimeofday(&start, NULL);   
   QuickSort(a1, size1, 0, size1 - 1);
   gettimeofday(&stop, NULL);
   time7 = (double)(stop.tv_sec - start.tv_sec) * 1000 + (double)(stop.tv_usec - start.tv_usec) / 1000;
   
   gettimeofday(&start, NULL);
   QuickSort(a2, size2, 0, size2 - 1);
   gettimeofday(&stop, NULL);
   time8 = (double)(stop.tv_sec - start.tv_sec) * 1000 + (double)(stop.tv_usec - start.tv_usec) / 1000;

   gettimeofday(&start, NULL);
   QuickSort(a3, size3, 0, size3 - 1);
   gettimeofday(&stop, NULL);
   time9 = (double)(stop.tv_sec - start.tv_sec) * 1000 + (double)(stop.tv_usec - start.tv_usec) / 1000;

   printf("//+-----------------------+-----------------+----------------+-------------+\n");
   printf("//|    Number of Elements |  Selection Sort | Insertion sort |   Quicksort |\n");
   printf("//+-----------------------+-----------------+----------------+-------------+\n");
   printf("//|                   %d|         %f|        %f|     %f|\n", size1, time1, time4, time7);
   printf("//|                  %d|       %f|        %f|   %f|\n", size2, time2, time5, time8);
   printf("//|                 %d|     %f|        %f| %f|\n", size3, time3, time6, time9);
   printf("//+-----------------------+-----------------+----------------+-------------+\n");
   
   return 0;
}

//  Sorts an Array of Integers Using Selection Sort
void SS(int A[], int size)
{
   int i, j, min, temp;
   //printArray(A, size);

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
      //printArray(A, size);
   }
}

// Sorts array using insertion sort
void InsertionSort(int A[], int size)
{
   int i;

   //printArray(A, size, 0);
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
      //printArray(A, size, i);
   }
}

// Sorts arry using quicksort
void QuickSort(int A[], int size, int leftIndex, int rightIndex)
{
   if(leftIndex < rightIndex)
   {
      int partition = HoarePartition(A, leftIndex, rightIndex);
      QuickSort(A, size, leftIndex, partition - 1);
      QuickSort(A, size, partition + 1, rightIndex);
      //printArray(A, size, leftIndex, rightIndex);
   }
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

// Swaps elements in array
void swap(int A[], int i, int j)
{
   int temp = A[i];
   A[i] = A[j];
   A[j] = temp;
}

//+-----------------------+-----------------+----------------+-------------+
//|    Number of Elements |  Selection Sort | Insertion sort |   Quicksort |
//+-----------------------+-----------------+----------------+-------------+
//|                   1000|         1.532000|        0.006000|     1.222000|
//|                  10000|       147.020000|        0.046000|   112.988000|
//|                 100000|     14661.284000|        0.466000| 11234.881000|
//+-----------------------+-----------------+----------------+-------------+

//+-----------------------+-----------------+----------------+-------------+
//|    Number of Elements |  Selection Sort | Insertion sort |   Quicksort |
//+-----------------------+-----------------+----------------+-------------+
//|                   1000|         1.520000|        0.033000|     1.238000|
//|                  10000|       146.875000|        0.049000|   112.734000|
//|                 100000|     14657.349000|        0.449000| 11216.946000|
//+-----------------------+-----------------+----------------+-------------+

//+-----------------------+-----------------+----------------+-------------+
//|    Number of Elements |  Selection Sort | Insertion sort |   Quicksort |
//+-----------------------+-----------------+----------------+-------------+
//|                   1000|         1.528000|        0.006000|     1.213000|
//|                  10000|       146.897000|        0.045000|   112.784000|
//|                 100000|     14637.614000|        0.458000| 11233.832000|
//+-----------------------+-----------------+----------------+-------------+
