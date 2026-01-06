/*********************************************
 * Id: vill9577
 *
 * w16.c
 * May 2, 2021
 *
 * Program Description:
 *   Quick Hull
 *
 * Source:
 *   https://rosettacode.org/wiki/Convex_hull#C
 *********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

// Struct for coordinates
typedef struct tPoint
{
   int x, y;
} Point;

// Convex hull function
Point *convexHull(Point p[], int len, int *hsize);

// Prints the points/coordinates of the convex hull
void printPoints(const Point *points, int len);

// Does a thing
bool ccw(const Point *a, const Point *b, const Point *c);

// Does another thing
int comparePoints(const void *lhs, const void *rhs);

// Does yet another thing
void fatal(const char *message);

// And another one
void* xmalloc(size_t n);

// More
void *xrealloc(void *p, size_t n);

int main(int argc, char *argv[])
{
   // End program if the command line does not have more than 7 arguments
   if(argc < 7)
   {
      printf(">  Error: INVALID INPUT\n\n");
      printf("   Please enter at least 7 command line arguments when executing\n");
      printf("      E.g. \" %s 0 0 1 0 0 1\"\n", argv[0]);
      printf("      I.e. (0, 0) , (1, 0) , (0, 1) which are coordinates\n\n");
      printf("   Exiting Program ...\n");
      return 1;
   }

   int i;
   int size = argc - 1;
   Point points[size];
   for(i = 0; i < size; i += 2)
   {
      //points[i] = {atoi(argv[i + 1]), atoi(argv[i + 2)};
      points[i].x = atoi(argv[i + 1]);
      points[i].y = atoi(argv[i + 2]);
      //printf("X: %d, Y: %d\n", points[i].x, points[i].y);
   }

   /*ALGORITHM HERE*/
   int hsize;
   Point *hull = convexHull(points, sizeof(points)/sizeof(Point), &hsize);
   printf("The points in Convex Hull are:\n");
   printPoints(hull, hsize);
   printf("\n");
   free(hull);

   return 0;
}

// Convex hull function
Point *convexHull(Point p[], int len, int *hsize)
{
   if(len == 0)
   {
      *hsize = 0;
      return NULL;
   }
 
   int i, size = 0, capacity = 4;
   Point *hull = xmalloc(capacity * sizeof(Point));
 
   qsort(p, len, sizeof(Point), comparePoints);
 
   /* lower hull */
   for(i = 0; i < len; ++i)
   {
      while(size >= 2 && !ccw(&hull[size - 2], &hull[size - 1], &p[i]))
      {
         --size;
      }
      if(size == capacity)
      {
         capacity *= 2;
         hull = xrealloc(hull, capacity * sizeof(Point));
      }
      assert(size >= 0 && size < capacity);
      hull[size++] = p[i];
   }
 
   /* upper hull */
   int t = size + 1;
   for(i = len - 1; i >= 0; i--)
   {
      while(size >= t && !ccw(&hull[size - 2], &hull[size - 1], &p[i]))
      {
         --size;
      }
      if(size == capacity)
      {
         capacity *= 2;
         hull = xrealloc(hull, capacity * sizeof(Point));
      }
      assert(size >= 0 && size < capacity);
      hull[size++] = p[i];
   }
   --size;
   assert(size >= 0);
   hull = xrealloc(hull, size * sizeof(Point));
   *hsize = size;
   return hull;
}

// Prints the points/coordinates of the convex hull
void printPoints(const Point *points, int len)
{
   //printf("[");
   if(len > 0)
   {
      const Point* ptr = points;
      const Point* end = points + len;
      printf("(%d, %d)", ptr->x, ptr->y);
      ++ptr;
      for(; ptr < end; ++ptr)
      {
         printf(", (%d, %d)", ptr->x, ptr->y);
      }
   }
   //printf("]");
}

// Does a thing
bool ccw(const Point *a, const Point *b, const Point *c)
{
   return (b->x - a->x) * (c->y - a->y) > (b->y - a->y) * (c->x - a->x);
}

// Does another thing
int comparePoints(const void *lhs, const void *rhs)
{
   const Point *lp = lhs;
   const Point *rp = rhs;
   if(lp->x < rp->x)
   {
      return -1;
   }
   if(rp->x < lp->x)
   {
      return 1;
   }
   if(lp->y < rp->y)
   {
      return -1;
   }
   if(rp->y < lp->y)
   {
      return 1;
   }
   return 0;
}

// Does yet another thing
void fatal(const char *message)
{
   fprintf(stderr, "%s\n", message);
   exit(1);
}

// And another one
void *xmalloc(size_t n)
{
   void *ptr = malloc(n);
   if (ptr == NULL)
   {
      fatal("Out of memory");
   }
   return ptr;
}

// More
void *xrealloc(void *p, size_t n)
{
   void *ptr = realloc(p, n);
   if (ptr == NULL)
   {
      fatal("Out of memory");
   }
   return ptr;
}
