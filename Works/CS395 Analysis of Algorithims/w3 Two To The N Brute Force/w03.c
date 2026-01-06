/*********************************************
 * Id: vill9577
 *
 * w03.c
 * January 22, 2021
 *
 * Program Description:
 *    Brute force 2^n algorithm
 *    
 *    Edit: Not supposed to use pow() or power()
 *    and TwoExpN not originally recursive (whoops!)
 *********************************************/

#include <stdio.h>
#include <stdlib.h>
//#include <math.h>  // pow() DOES NOT WORK WITH SUBMISSION (Edit: not supposed to use)


// Recursive function for 2^n
int TwoExpN(int n);

// pow() Submission workaround taken from GeeksForGeeks.org
//int power(int a, int b);


int main(int argc, char *argv[])
{
   // End program if the command line does not have exactly 2 arguments
   if(argc != 2)
   {
      printf(">  Error: INVALID INPUT\n\n");
      printf("   Please enter 2 command line arguments when executing\n");
      printf("      E.g. \"1) %s POSITIVE INTEGER\"\n", argv[0]);
      printf("           \"2) %s 5\"\n\n", argv[0]);
      printf("   Exiting Program ...\n");
      return 1;
   }

   /* ALGORITHM HERE */
   int n = atoi(argv[1]);
   printf("2^%d: %d\n", n, TwoExpN(n));

   return 0;
}

// Recursive function for 2^n
int TwoExpN(int n)
{
   if(n < 1)
   {
      return 1;
   }
   else
   {
      // BELOW pow() DOES NOT WORK WITH SUBMISSION
      //return ((int)pow(2, n - 1) + (int)pow(2, n - 1));
      //return (power(2, n - 1) + power(2, n - 1));

      return (TwoExpN(n - 1) + TwoExpN(n-1));  // FIXED
   }
}

/*// pow() Submission workaround taken from GeeksForGeeks.org
int power(int a, int b)
{
   if(b == 0)
   {
      return 1;
   }
   else if(b % 2 == 0)
   {
      return power(a, b/2) * power(a, b/2);
   }
   else
   {
      return a * power(a, b/2) * power(a, b/2);
   }
}
*/
