/*********************************************
 * Id: vill9577
 *
 * w13.c
 * April 30, 2021
 *
 * Program Description:
 *   Permutations
 *********************************************/

#include <stdio.h>
#include <stdlib.h>

// Print array
void printPerm(int a[], int n);

// Generate permutation using heap algorithm
void heapPerm(int a[], int size, int n); 

// Swaps elements in array
void swap(int a[], int i, int j);

int main(int argc, char *argv[])
{
   // End program if the command line does not have exactly 3 arguments
   if(argc != 2)
   {
      printf(">  Error: INVALID INPUT\n\n");
      printf("   Please enter exactly 2 command line arguments when executing\n");
      printf("      E.g. \" %s 3 \"\n\n", argv[0]);
      printf("   Exiting Program ...\n");
      return 1;
   }

   int n = atoi(argv[1]);
   int a[n];
   int i;
   for(i = 0; i < n; i++)
   {
      a[i] = i + 1;
   }

   /*ALGORITHM HERE*/
   heapPerm(a, n, n);

   return 0;
}

// Print array
void printPerm(int a[], int n)
{
   int i;
   for(i = 0; i < n; i++)
   {
      printf("%d", a[i]);
   }
   printf("\n");
}



// Generate permutation using heap algorithm
void heapPerm(int a[], int size, int n)
{
   // If size becomes 1 print obtained permutation
   if(size == 1)
   {
      printPerm(a, n);
      return;
   }

   int i;
   for(i = 0; i < size; i++)
   {
      heapPerm(a, size - 1, n);

      // If size is odd, first and last element
      if(size % 2 == 1)
      {
         swap(a, 0, size - 1);
      }
      // Else if size is even, swap ith and last element
      else
      {
         swap(a, i, size - 1);
      }
   }
}

// Swaps elements in array
void swap(int A[], int i, int j)
{
   int temp = A[i];
   A[i] = A[j];
   A[j] = temp;
}

