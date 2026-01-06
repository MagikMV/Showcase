/*********************************************
 * Id: vill9577
 *
 * w13.c
 * April 25, 2021
 *
 * Program Description:
 *   Russian Peasant Multiplication
 *********************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
   // End program if the command line does not have exactly 3 arguments
   if(argc != 3)
   {
      printf(">  Error: INVALID INPUT\n\n");
      printf("   Please enter exactly 3 command line arguments when executing\n");
      printf("      E.g. \" %s 50 65 \"\n\n", argv[0]);
      printf("   Exiting Program ...\n");
      return 1;
   }

   /*ALGORITHM HERE*/
   int n, m, sum;
   n = atoi(argv[1]);
   m = atoi(argv[2]);
   sum = 0;

   while(n > 0)
   {
      if(n % 2 != 0)
      {
         sum += m;
         printf("%6d %6d %6d\n", n, m, m);
      }
      else
      {
         printf("%6d %6d\n", n, m);
      }

      m *= 2;  // Double
      n /= 2;  // Half
   }

   // Last lines
   printf("%20s\n", "------");
   printf("%20d\n", sum);

   return 0;
}
