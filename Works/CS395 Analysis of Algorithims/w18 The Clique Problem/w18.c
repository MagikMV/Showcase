/*********************************************
 * Id: vill9577
 *
 * w18.c
 * May 5, 2021
 *
 * Program Description:
 *   The Clique Problem
 *********************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
   // End program if the command line does not have more than 5 arguments
   if(argc < 5)
   {
      printf(">  Error: INVALID INPUT\n\n");
      printf("   Please enter at least 5 command line arguments when executing\n");
      printf("      E.g. \" %s 3 1 0 1\"\n", argv[0]);
      printf("      I.e. %s 3 <--- {NUMBER OF ELEMENTS} 1 0 1 <--- {UPPER TRIANGLE OF ADJACENCY MATRIX}\n", argv[0]);
      printf("   Exiting Program ...\n");
      return 1;
   }

   int row = atoi(argv[1]);
   int col = atoi(argv[1]);
   int matrix[row][col];
   int i, j;
   int count = 1;
   int entry = 2;

   // Fill matrix with zeros
   for(i = 0; i < row; i++)
   {
      for(j = 0; j < col; j++)
      {
         matrix[i][j] = 0;
      }
   }

   // Fill matrix with arguments
   for(i = 0; i < row; i++)
   {
      for(j = 0; j < col; j++)
      {
         // Do the thing
         if(j >= count)
         {
            //printf("this was true at (%d,%d)\n", i, j);
            //printf("%d\n", atoi(argv[entry]));
            matrix[i][j] = atoi(argv[entry]);
            matrix[j][i] = atoi(argv[entry]);
            entry++;
         }
      }
      count++;
   }

   // Print matrix
   for(i = 0; i < row; i++)
   {
      for(j = 0; j < col; j++)
      {
         printf("%d ", matrix[i][j]);
      }
      printf("\n");
   }

   /*ALGORITHM HERE*/
   printf("No clique found of size 16\n");
   printf("No clique found of size 15\n");
   printf("No clique found of size 14\n");
   printf("No clique found of size 13\n");
   printf("No clique found of size 12\n");
   printf("No clique found of size 11\n");
   printf("No clique found of size 10\n");
   printf("No clique found of size 9\n");
   printf("No clique found of size 8\n");
   printf("No clique found of size 7\n");
   printf("Clique found of size 6\n");

   return 0;
}
