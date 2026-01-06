/*********************************************
 * Id: vill9577
 *
 * w06.c
 * February 19, 2021
 *
 * Program Description:
 *    Cyclic Tower of Hanoi
 *********************************************/

#include <stdio.h>
#include <stdlib.h>

// Recursive function for solving Cyclic Tower of Hanoi Puzzle
void CyclicHanoi(int nDisks, char fromPeg, char toPeg, char withPeg);

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
   CyclicHanoi(nDisks, fromPeg, toPeg, withPeg);

   return 0;
}

// Recursive function for solving Cyclic Tower of Hanoi Puzzle
void CyclicHanoi(int nDisks, char fromPeg, char toPeg, char withPeg)
{
   if(nDisks == 1)
   {
      printf("MOVE %c TO %c\n", fromPeg, withPeg);
      printf("MOVE %c TO %c\n", withPeg, toPeg);
   }
   else if(nDisks > 1)
   {
      CyclicHanoi(nDisks - 1, fromPeg, toPeg, withPeg);
      printf("MOVE %c TO %c\n", fromPeg, withPeg);
      CyclicHanoi(nDisks - 2, toPeg, withPeg, fromPeg); // added
      printf("MOVE %c TO %c\n", toPeg, fromPeg);
      CyclicHanoi(nDisks - 2, withPeg, fromPeg, toPeg); // added
      printf("MOVE %c TO %c\n", withPeg, toPeg);
      CyclicHanoi(nDisks - 1, fromPeg, toPeg, withPeg);
      //printf("6MOVE %c TO %c\n", fromPeg, withPeg);
      //CyclicHanoi(nDisks - 1, toPeg, withPeg, fromPeg);
   }

   /*printf("%d\n", nDisks);
   if(nDisks == 1)
   {
      printf("1MOVE %c TO %c\n", fromPeg, withPeg);
      //printf("2MOVE %c TO %c\n", withPeg, toPeg);
      //printf("3MOVE %c TO %c\n", fromPeg, withPeg);
   }
   else if(nDisks > 1)
   {
      CyclicHanoi(nDisks - 1, fromPeg, toPeg, withPeg);
      printf("2MOVE %c TO %c\n", withPeg, toPeg);
      //printf("4MOVE %c TO %c\n", withPeg, toPeg);
      //printf("4MOVE %c TO %c\n", toPeg, fromPeg);
      printf("3MOVE %c TO %c\n", fromPeg, withPeg);
      CyclicHanoi(nDisks - 1, toPeg, withPeg, fromPeg);
      printf("4MOVE %c TO %c\n", withPeg, toPeg);
      //printf("5MOVE %c TO %c\n", fromPeg, withPeg);
      CyclicHanoi(nDisks - 1, fromPeg, toPeg, withPeg);
      printf("5MOVE %c TO %c\n", withPeg, toPeg);
      CyclicHanoi(nDisks - 1, fromPeg, toPeg, withPeg);
   }
   printf("%d\n", nDisks);*/
}

