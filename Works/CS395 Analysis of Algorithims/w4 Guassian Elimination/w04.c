/*********************************************
 * Id: vill9577
 *
 * w04.c
 * February 4, 2021
 *
 * Program Description:
 *    Guassian Elimination
 *********************************************/

#include <stdio.h>
#include <stdlib.h>

// Function that prints the system of equations (or matrix)
void printMatrix(int n, float A[n][n+1]);

int main(int argc, char *argv[])
{
   // End program if the command line does not have enough arguments
   if(argc == 1 || argc < (atoi(argv[1]) * (atoi(argv[1]) + 1)) + 2)
   {
      printf(">  Error: INVALID INPUT\n\n");
      printf("   Please enter enough command line arguments when executing\n");
      printf("      E.g. \" %s 3 1 2 3 4 5 6 7 8 9 10 11 12 \"\n", argv[0]);
      printf("      NOT: \" %s 2 1 2 3 4 5 \"\n\n", argv[0]);
      printf("   Exiting Program ...\n");
      return 1;
   }

   int n = atoi(argv[1]);
   float Arr[n][n+1];
   int i, j, k;
   int count = 0;
   float tempji;

   for(i = 0; i < n; i++)
   {
      for(j = 0; j < n + 1; j++)
      {
         Arr[i][j] = atof(argv[count + 2]);
         count++;
      }
   }
   
   printMatrix(n, Arr);

   /* ALGORITHM HERE */
   i = 0;
   j = 0;
   //printf("I am outside\n");
   //printf("i & j & k: %d %d %d\n\n", i, j, k);
   for(i = 0; i < n; i++)
   {
      //printf("I am here\n");
      for(j = i + 1; j < n + 1; j++)
      {
         //printf("I am here\n");
         tempji = Arr[j][i];
         for(k = i; k < n + 1; k++)
         {
            //printf("I am here\n");
            Arr[j][k] = Arr[j][k] - (Arr[i][k] * tempji / Arr[i][i]);
         }
      }
      printMatrix(n, Arr);
   }   
   //printf("I am done\n");
   //printf("i & j & k: %d %d %d\n\n", i, j, k);

   return 0;
}

// Function that prints the system of equations (or matrix)
void printMatrix(int n, float A[n][n+1])
{
   int i, j;

   for(i = 0; i < n; i++)
   {
      for(j = 0; j < n + 1; j++)
      {
         printf("%.2f ", A[i][j]); 
      }
      printf("\n");
   }
   printf("\n");
}
