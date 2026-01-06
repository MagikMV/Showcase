/* sort.cpp
 */

#include <iostream>
#include <cstdlib>
using namespace std;

#include "sort.h"

// SelectionSort
    // Sorts a given array using the selection sort algorithm
void SelectionSort(int A[], int nElements, int &nComparisons, int &nSwaps)
{
    int iSmallest;
    for(int i = 0; i < nElements; i++)
    {
        iSmallest = IndexOfSmallest(A, i, nElements - 1, nComparisons);
        if(iSmallest > i)
        {
            Swap(A[i], A[iSmallest],nSwaps);
        }  
    }
}

// IndexOfSmallest
    // Finds the index of the smallest value
int IndexOfSmallest(int A[], int iStart, int iEnd, int &nComparisons)
{
    int index = 0;
    int aMin = A[iStart];
    for(int i = iStart; i <= iEnd; i++)
    {
        if(A[i] < aMin)
        {
            aMin = A[i];
            index = i;
        }
        nComparisons += 1;
    }
    return index;
}

// MergeSort
    // Sorts a given array using the mergesort algorithm
void MergeSort(int A[], int first, int last, int &nComparisons, int &nSwaps, int size)
{
    int middle;
    if(first < last)
    {
        middle = (first + last) / 2;
        MergeSort(A, first, middle, nComparisons, nSwaps, size);
        MergeSort(A, middle + 1, last, nComparisons, nSwaps, size);
        Merge(A, first, middle, middle + 1, last, nComparisons, nSwaps, size);
    }
}

// Merge
    // Merges two segments of an array together
void Merge(int A[], int firstLeft, int lastLeft, int firstRight, int lastRight,
           int &nComparisons, int &nSwaps, int size)
{
    int firstSave = firstLeft;

    int tempA[size];
    int index = firstLeft;
        // Merge Segments
    while((firstLeft <= lastLeft) && (firstRight <= lastRight))
    {
        if(A[firstLeft] < A[firstRight])
        {
            tempA[index] = A[firstLeft];
            firstLeft++;
        }
        else
        {
            tempA[index] = A[firstRight];
            firstRight++;
            nSwaps += 1;
        }
        nComparisons += 1;
        index++;        
    }
        // Copy remainder of left array into tempA
    while(firstLeft <= lastLeft)
    {
        tempA[index] = A[firstLeft];
        firstLeft++;
        nSwaps += 1;
        index++;
    }
        // Copy remainder of right array into tempA
    while(firstRight <= lastRight)
    {
        tempA[index] = A[firstRight];
        firstRight++;
        index++;
    }
        // Copy back into original array
    for(index = firstSave; index <= lastRight; index++)
    {
        A[index] = tempA[index];
    }
}

// QuickSort
    // Sorts a given array using the quicksort algorithm
void QuickSort(int A[], int first, int last, int &nComparisons, int &nSwaps)
{
    int pivot;

    if(first < last)
    {
        pivot = Pivot(A, first, last, nComparisons, nSwaps);
        QuickSort(A, first, pivot - 1, nComparisons, nSwaps);
        QuickSort(A, pivot + 1, last, nComparisons, nSwaps);
    }
}

// Pivot
    // Finds and returns the index of the pivot element
int Pivot(int A[], int first, int last, int &nComparisons, int &nSwaps)
{
    int p = first;
    int pivot = A[first];

    for(int i = first + 1; i <= last; i++)
    {
        if(A[i] <= pivot)
        {
            p++;
            Swap(A[i], A[p], nSwaps);
        }
        nComparisons += 1;
    }
    Swap(A[p], A[first], nSwaps);

    return p;
}

// Swap
    // Swaps two values (by reference)
void Swap(int &v1, int &v2, int &nSwaps)
{
    nSwaps += 1;

    int tmpVal = v1;
    v1 = v2;
    v2 = tmpVal;
}

// GenerateRandom
    // Returns a randomly sorted array of size 'n'
int* GenerateRandom(int size)
{
    int *p = new int[size];

    for(int i = 0; i < size; i++)
    {
        p[i] = rand() % size + 1;
    }
    return p;
}

// GenerateLowHigh
    // Returns an array sorted low to high of size 'n'
int* GenerateLowHigh(int size)
{
    int *p = new int[size];

    for(int i = 0; i < size; i++)
    {
        p[i] = i + 1;
    }
    return p;
}

// GenerateHighLow
    // Returns an array sorted high to low of size 'n'
int* GenerateHighLow(int size)
{
    int *p = new int[size];
    int index = 0;

    for(int i = size; i > 0; i--)
    {
        p[index] = i;
        index += 1;
    }
    return p;
}

// DisaplyComSwaps
    // Displays the number of comparisons and swaps for a given sort
void DisplayComSwaps(int &nComparisons, int &nSwaps)
{
    cout << "\t" << "Number of swaps: " << nSwaps << endl;
    cout << "\t" << "Number of comparisons: " << nComparisons << endl;

    // Reset counters for next sort
    nComparisons = 0;
    nSwaps = 0;
}