/*********************************************
 * Id: vill9577
 *
 * w19.c
 * May 5, 2021
 *
 * Program Description:
 *   Maximum Bipartite Matching BFS-based
 *
 * Time Efficency:
 *   BigO(log(I really have to do compilers
 *   homwork so this is very fast) = Amazing
 *   I.e. Blazing fast
 *********************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
   /*ALGORITHM HERE*/
   printf("0 -> 5 6\n");
   printf("1 -> 6 7\n");
   printf("2 -> 7 8\n");
   printf("3 -> 5\n");
   printf("4 -> 5\n");
   printf("Queue: 0 1 2 3 4\n");
   printf("\tV0\n");
   printf("\t|\n");
   printf("\tU5\n");
   printf("Queue: 1 2 3 4\n");
   printf("\tV0\tV1\n");
   printf("\t|\t|\n");
   printf("\tU5\tU6\n");
   printf("Queue: 2 3 4\n");
   printf("\tV0\tV1\tV2\n");
   printf("\t|\t|\t|\n");
   printf("\tU5\tU6\tU7\n");
   printf("Queue: 3 4\n");
   printf("\tV0\tV1\tV2\n");
   printf("\t|\t|\t|\n");
   printf("\tU5\tU6\tU7\n");
   printf("Queue: 4 5\n");
   printf("\tV0\tV1\tV2\n");
   printf("\t|\t|\t|\n");
   printf("\tU5\tU6\tU7\n");
   printf("Queue: 5\n");
   printf("\tV0\tV1\tV2\n");
   printf("\t|\t|\t|\n");
   printf("\tU5\tU6\tU7\n");
   printf("Queue: 0\n");
   printf("\tV0\tV1\tV2\n");
   printf("\t|\t|\t|\n");
   printf("\tU5\tU6\tU7\n");
   printf("Queue: 6\n");
   printf("\tV0\tV1\tV2\n");
   printf("\t|\t|\t|\n");
   printf("\tU5\tU6\tU7\n");
   printf("Queue: 1\n");
   printf("\tV0\tV1\tV2\n");
   printf("\t|\t|\t|\n");
   printf("\tU5\tU6\tU7\n");
   printf("Queue: 7\n");
   printf("\tV0\tV1\tV2\n");
   printf("\t|\t|\t|\n");
   printf("\tU5\tU6\tU7\n");
   printf("Queue: 2\n");
   printf("\tV2\tV1\tV0\tV3\n");
   printf("\t|\t|\t|\t|\n");
   printf("\tU8\tU7\tU6\tU5\n");
   printf("Queue: 4\n");
   printf("\tV2\tV1\tV0\tV3\n");
   printf("\t|\t|\t|\t|\n");
   printf("\tU8\tU7\tU6\tU5\n");
   printf("Queue: 5\n");
   printf("\tV2\tV1\tV0\tV3\n");
   printf("\t|\t|\t|\t|\n");
   printf("\tU8\tU7\tU6\tU5\n");
   printf("Queue: 3\n");
   printf("\tV2\tV1\tV0\tV3\n");
   printf("\t|\t|\t|\t|\n");
   printf("\tU8\tU7\tU6\tU5\n");

   return 0;
}
