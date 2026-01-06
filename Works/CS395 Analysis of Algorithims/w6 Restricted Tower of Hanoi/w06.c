/*********************************************
 * Id: vill9577
 *
 * w06.c
 * February 9, 2021
 *
 * Program Description:
 *    Restricted Tower of Hanoi
 *********************************************/

#include <stdio.h>
#include <stdlib.h>

// Recursive function for solving Restricted Tower of Hanoi Puzzle
void RestrictedHanoi(int nDisks, char fromPeg, char toPeg, char withPeg);

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
   RestrictedHanoi(nDisks, fromPeg, toPeg, withPeg);

   return 0;
}

// Recursive function for solving Restricted Tower of Hanoi Puzzle
void RestrictedHanoi(int nDisks, char fromPeg, char toPeg, char withPeg)
{
   if(nDisks == 1)
   {
      printf("MOVE %c TO %c\n", fromPeg, withPeg);
      printf("MOVE %c TO %c\n", withPeg, toPeg);
   }
   else if(nDisks > 1)
   {
      RestrictedHanoi(nDisks - 1, fromPeg, toPeg, withPeg);
      printf("MOVE %c TO %c\n", fromPeg, withPeg);
      RestrictedHanoi(nDisks - 1, toPeg, fromPeg, withPeg);
      printf("MOVE %c TO %c\n", withPeg, toPeg);
      RestrictedHanoi(nDisks - 1, fromPeg, toPeg, withPeg);
   }
}

