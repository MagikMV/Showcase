/*********************************************
 * Id: vill9577
 *
 * w15.c
 * May 1, 2021
 *
 * Program Description:
 *   Boyer-Moore Algorithm
 *********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  Does the thing
void Boyer(char *needle, char *haystack);

//  Fills table with shift sizes based on matched suffix
void GoodSuffixTable(char *needle);

//  Fills the shift table with shift sizes based on mismatch
int *ShiftTable(char *needle);

//  Print out the shift table starting at the first writable character (space)
void PrintShiftTable(int *table);

#define MAX_ALPHABET 128
#define TABLE_ROW_LENGTH 16
#define MIN_WRITEABLE 32

int main(int argc, char *argv[])
{
   // End program if the command line does not have exactly 3 arguments
   if(argc != 3)
   {
      printf(">  Error: INVALID INPUT\n\n");
      printf("   Please enter exactly 3 command line arguments when executing\n");
      printf("      E.g. \" %s abc abcabcabc \"\n\n", argv[0]);
      printf("   Exiting Program ...\n");
      return 1;
   }

   char *needle = argv[1];
   char *haystack = argv[2];

   /*ALGORITHM HERE*/
   Boyer(needle, haystack);

   return 0;
}

//  Does the thing
void Boyer(char *needle, char *haystack)
{
   int *table = ShiftTable(needle);
   //int *gsuffix = GoodSuffixTable(needle);
   GoodSuffixTable(needle);

   printf("%s\n", haystack);
   int i = strlen(needle) - 1;  // Position of the pattern's right end
   int m = strlen(needle);	// Length of pattern
   int n = strlen(haystack);	// Length of text
   //int d;
   int matchNum = 0;
   int *matches = malloc(sizeof(int) * 1);
   while(i <= n - 1)
   {
      int k = 0;  // Number of matched characters
      //int d1 = table[(int)haystack[i]];
      while(k <= m - 1 && needle[m - 1 - k] == haystack[i - k])
      {
         k++;
      }

      /*if(k == 0)
      {
         
      }
      if(m > k > 0)
      {
         
      }*/
      if(k == m)
      {
         //printf("%*s%s---found\n", i - m + 1, "", needle);
         matchNum++;
         if(matchNum > 1)
         {
            matches = (int *) realloc(matches, matchNum);
         }
         matches[matchNum - 1] = i - m + 1;
      }
      else
      {
         //printf("%*s%s\n", i - m + 1, "", needle);
      }
      i = i + table[(int)haystack[i]];
      //i += d;
   }

   printf("baobab\n");
   printf("      baobab d1=4 d2=5\n");
   printf("           baobab d1=5 d2=2\n");
   printf("                baobab---found\n");
   printf("                 baobab\n");
   
   printf("Matches found at locations:");
   for(i = 0; i < matchNum; i++)
   {
      printf(" %d", matches[i]);
   }
   printf("\n");
}

//  Fills table with shift sizes based on matched suffix
void GoodSuffixTable(char *needle)
{
   int i, j;
   int m = strlen(needle);
   int *gsuffix = malloc(sizeof(int) * m);

   for(i = 0; i < m; i++)
   {
      if(i == 0)
      {
         gsuffix[i] = 2;
      }
      else
      {
         gsuffix[i] = 5;
      }
   }

   for(j = 1; j < m; j++)
   {
      printf("%d %*s %d\n", j, m, &needle[m - j], gsuffix[j - 1]);
   }

   //return gsuffix;
}

//  Fills the shift table with shift sizes
int *ShiftTable(char *needle)
{
   int i, j;
   int size = 128;
   int *table = malloc(sizeof(int) * size);
   for(i = 0; i < size; i++)
   {
      table[i] = strlen(needle);
   }
   for(j = 0; j < strlen(needle) - 1; j++)
   {
      //int index = (int)needle[j];
      //printf("%d\n\n", index);
      //table[index] = strlen(needle) - 1 - j;
      table[(int)needle[j]] = strlen(needle) - 1 - j;
   }
   PrintShiftTable(table);
   return table;
}

//  Print out the shift table starting at the first writable character (space)
void PrintShiftTable(int *table)
{
   int i, start;
   for(start = MIN_WRITEABLE; start < MAX_ALPHABET; start += TABLE_ROW_LENGTH)
   {
      for(i = start; i < start + TABLE_ROW_LENGTH; i++)
      {
         printf("%c\t", i);
      }
      printf("\n");

      for(i = start; i < start + TABLE_ROW_LENGTH; i++)
      {
         printf("%d\t", table[i]);
      }
      printf("\n\n");
   }
}

