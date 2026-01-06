/*********************************************
 * Id: vill9577
 *
 * Miguel Villanueva
 * January 21, 2021
 *
 * Program Description:
 *    Improves the following:
 *    This program takes in an array of integers as input from the command line. The
 *    array must consist of at least two elements. This is because this program
 *    implements a minimum distance algorithm. The objective is to find the distance
 *    between the closest elements of the input array.
 * 
 *    E.g. [Input]: 1 3 7, [Output]: 2
 *********************************************/

#include <stdio.h>
#include <stdlib.h>

//  Finds the distance from 'a' to 'b', where 'a' and 'b' are positive integers in the array 
int dist(int a, int b);

int main(int argc, char *argv[])
{
   //  End program if the command line has less than 3 arguments
   if(argc < 3)
   {
      printf(">  Error: INVALID INPUT\n\n");
      printf("   Please enter at least 3 command line arguments when executing\n");
      printf("      E.g. \"%s 3 7\"\n\n", argv[0]);
      printf("   Exiting Program ...\n");
      return 1;
   }

   /* ALOGRITHM HERE */
   int i, j;
   int minDist = dist(atoi(argv[1]), atoi(argv[2]));
   for(i = 1; i < argc; i++)
   {
      // Changed from "for(j = 1...)", which lessens comparisons
      for(j = i + 1; j < argc; j++)
      {
         if(i != j && dist(atoi(argv[i]), atoi(argv[j])) < minDist)
         {
            minDist = dist(atoi(argv[i]), atoi(argv[j]));
         }
      }
   }
   printf("Minimum distance: %d\n", minDist);

   return 0;
}

//  Finds the distance from 'a' to 'b', where 'a' and 'b' are positive integers in the array
int dist(int a, int b)
{
   int result = a - b;
   if(result < 0)
   {
      result = b - a;
   }
   return result;
}
