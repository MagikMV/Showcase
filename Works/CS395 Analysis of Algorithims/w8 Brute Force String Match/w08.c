/*********************************************
 * Id: vill9577
 *
 * w08.c
 * February 25, 2021
 *
 * Program Description:
 *   Brute Force String Match
 *********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// String Matching Using Brute Force
void BruteForceStringMatch(char *T, char *P);

int main(int argc, char *argv[])
{
   // End program if the command line does not have 2 arguments
   if(argc != 3)
   {
      printf(">  Error: INVALID INPUT\n\n");
      printf("   Please enter 3 command line arguments when executing\n");
      printf("      E.g. \" %s a abaa \"\n\n", argv[0]);
      printf("   Exiting Program ...\n");
      return 1;
   }

   char *P = argv[1];   // Pattern
   char *T = argv[2];   // Text
   
   /* ALGORITHM HERE */
   printf("Matches found at locations:");
   BruteForceStringMatch(T, P);
   printf("\n");

   return 0;
}

// String Matching Using Brute Force
void BruteForceStringMatch(char *T, char *P)
{
   int i, j;
   //for(i = 0; i < (strlen(T) - strlen(P)); i++)
   for(i = 0; i < strlen(T); i++)  // CHANGED
   {
      j = 0;
      while(j < strlen(P) && P[j] == T[i+j])
      {
         j = j + 1;
      }
      if(j == strlen(P))
      {
         printf(" %d", i);
      }
   }
}
