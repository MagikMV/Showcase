/* sort.h
 */

#ifndef SORT_H
#define SORT_H

#include <iostream>
using namespace std;

//  Selection Sort
void SelectionSort(int A[], int nElements, int &nComparisons, int &nSwaps);
int IndexOfSmallest(int A[], int iStart, int iEnd, int &nComparisons);

//  Merge Sort
void MergeSort(int A[], int first, int last, int &nComparisons, int &nSwaps, int size);
void Merge(int A[], int firstLeft, int lastLeft, int firstRight, int lastRight,
           int &nComparisons, int &nSwaps, int size);

//  Quick Sort
void QuickSort(int A[], int first, int last, int &nComparisons, int &nSwaps);
int Pivot(int A[], int first, int last, int &nComparisons, int &nSwaps);

//  Miscellaneous
void Swap(int &v1, int &v2, int &nSwaps);

int* GenerateRandom(int size);
int* GenerateLowHigh(int size);
int* GenerateHighLow(int size);
void DisplayComSwaps(int &nComparisons, int &nSwaps);

#endif // SORT_H