/*********************************************
 * Id: vill9577
 *
 * w17.c
 * May 4, 2021
 *
 * Program Description:
 *   Modified Robot Coin Collecting
 *********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Returns the max of two integers
int max(int x, int y);

// Returns the largest number of coins robot can collect
int RobotCC(int n, int m, int matrix[][m]);

int main(int argc, char *argv[])
{
   // End program if the command line does not have more than 7 arguments
   if(argc < 7)
   {
      printf(">  Error: INVALID INPUT\n\n");
      printf("   Please enter at least 7 command line arguments when executing\n");
      printf("      E.g. \" %s 2 2 0 1 X 1\"\n", argv[0]);
      printf("   Exiting Program ...\n");
      return 1;
   }

   int n = atoi(argv[1]);  // Number of rows
   int m = atoi(argv[2]);  // Number of columns
   int matrix[n][m];
   int optimalPath;
   int i, j;
   int count = 3;

   printf("Board Inputed:\n");
   for(i = 0; i < n; i++)
   {
      for(j = 0; j < m; j++)
      {
         if(strcmp(argv[count], (char *)"X") == 0)
         {
            matrix[i][j] = -1;
            printf("%c\t", 88);
         }
         else
         {
            matrix[i][j] = atoi(argv[count]);
            printf("%d\t", matrix[i][j]);
         }
         count++;
      }
      printf("\n");
   }
   printf("\n");

   /*ALGORITHM HERE*/
   optimalPath = RobotCC(n, m, matrix);
   printf("The optimal path with this board is: %d\n", optimalPath);

   return 0;
}

// Returns the max of two integers
int max(int x, int y)
{
   if(x > y)
   {
      return x;
   }
   else
   {
      return y;
   }
}

// Returns the largest number of coins robot can collect
int RobotCC(int n, int m, int matrix[][m])
{
   int table[n][m];
   int a, b;
   // Set values in coin collection table to zero
   for(a = 0; a < n; a++)
   {
      for(b = 0; b < m; b++)
      {
         table[a][b] = 0;
      } 
   }

   // Do the thing
   int i, j;
   bool firstColDone = false;
   //bool lastRow = false;
   table[0][0] = matrix[0][0];
   for(j = 1; j < m; j++)  // First row
   {
      if(matrix[0][j] == -1)
      {
         break;
      }
      else
      {
         // Index is equal to left value + value in matrix
         table[0][j] = table[0][j-1] + matrix[0][j];
      }
   }
   for(i = 1; i < n; i++)  // First column
   {
      if(matrix[i][0] == -1)
      {
         firstColDone = true;
      }
      if(firstColDone != true)
      {
         // Index is equal to value above + value in matrix
         table[i][0] = table[i-1][0] + matrix[i][0];
      }
      /*if(i == n - 1)
      {
         lastRow = true;
      }*/
      for(j = 1; j < m; j++)  // Current row
      {
         /*if(!lastRow)
         {
            if(matrix[i][j] == -1)
            {
               break;
            }
            // Index is equal to the max of (value above or value to the left) + value in matrix
            table[i][j] = max(table[i-1][j], table[i][j-1]) + matrix[i][j];
         }
         //else
         //{*/
            if(matrix[i][j] == -1)
            {
               table[i][j] = 0;
               continue;
            }
            // Index is equal to the max of (value above or value to the left) + value in matrix
            table[i][j] = max(table[i-1][j], table[i][j-1]) + matrix[i][j];
         //}
      }
   }

   printf("Coin Collecting Table:\n");
   for(i = 0; i < n; i++)
   {
      for(j = 0; j < m; j++)
      {
         printf("%d\t", table[i][j]);
      }
      printf("\n");
   }
   printf("\n");

   return table[n-1][m-1];
}
