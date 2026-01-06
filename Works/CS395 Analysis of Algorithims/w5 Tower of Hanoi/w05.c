/*********************************************
 * Id: vill9577
 *
 * w05.c
 * February 5, 2021
 *
 * Program Description:
 *    Tower of Hanoi
 *********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Recursive function for solving Tower of Hanoi Puzzle
void TowerOfHanoi(int nDisks, char fromPeg, char toPeg, char withPeg);

int main(int argc, char *argv[])
{
   // End program if the command line does not have 2 arguments
   if(argc != 2)
   {
      printf(">  Error: INVALID INPUT\n\n");
      printf("   Please enter 2 command line arguments when executing\n");
      printf("      E.g. \" %s 3 \"\n\n", argv[0]);
      printf("   Exiting Program ...\n");
      return 1;
   }

   int nDisks = atoi(argv[1]);
   char fromPeg = 'A';
   char toPeg = 'C';
   char withPeg = 'B';

   /* ALGORITHM HERE */
   TowerOfHanoi(nDisks, fromPeg, toPeg, withPeg);

   return 0;
}

// Recursive function for solving Tower of Hanoi Puzzle
void TowerOfHanoi(int nDisks, char fromPeg, char toPeg, char withPeg)
{
   if(nDisks == 1)
   {
      printf("MOVE %c TO %c\n", fromPeg, toPeg);
   }
   else if(nDisks > 1)
   {
      TowerOfHanoi(nDisks - 1, fromPeg, withPeg, toPeg);
      printf("MOVE %c TO %c\n", fromPeg, toPeg);
      TowerOfHanoi(nDisks - 1, withPeg, toPeg, fromPeg);
   }
}

