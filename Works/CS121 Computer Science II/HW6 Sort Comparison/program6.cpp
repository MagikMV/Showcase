/* program6.cpp
 *
 * CS 121 Bolden
 * Miguel Villanueva  //  vill9577@vandals.uidaho.edu
 * December 1, 2019
 *
 * Eluktronics P65_67HSHP  //  Intel Core i7-7700HQ
 * GCC Ubuntu 7.4.0
 */

#include <iostream>
using namespace std;

#include "sort.h"

int main()
{
    int comparisons = 0;
    int swaps = 0;
    // Run selection, merge, and quick sort on nine data sets each 
    for(int i = 0; i < 3; i++)
    {
        // Generation of data sets
            // Random
        int *A1 = GenerateRandom(100);
        int *A4 = GenerateRandom(1000);
        int *A7 = GenerateRandom(10000);
            // Low to high
        int *A2 = GenerateLowHigh(100);
        int *A5 = GenerateLowHigh(1000);
        int *A8 = GenerateLowHigh(10000);
            // High to low
        int *A3 = GenerateHighLow(100);
        int *A6 = GenerateHighLow(1000);
        int *A9 = GenerateHighLow(10000);
        // Selection Sort
        if(i == 0)
        {
            cout << "------------------------";
            cout << "------------------------" << endl;
            cout << "Selection sort:" << endl;
            cout << "------------------------";
            cout << "------------------------" << endl;
            // Magnitude: 100
            cout << "Data set magnitude: 100" << endl;
            cout << "    "<< "Random set" << endl;
            SelectionSort(A1, 100, comparisons, swaps);
            DisplayComSwaps(comparisons, swaps);
            cout << "    " << "Low to high set" << endl;
            SelectionSort(A2, 100, comparisons, swaps);
            DisplayComSwaps(comparisons, swaps);
            cout << "    " << "High to low set" << endl;
            SelectionSort(A3, 100, comparisons, swaps);
            DisplayComSwaps(comparisons, swaps);
            cout << endl;

            // Magnitude: 1000
            cout << "Data set magnitude: 1000" << endl;
            cout << "    "<< "Random set" << endl;
            SelectionSort(A4, 1000, comparisons, swaps);
            DisplayComSwaps(comparisons, swaps);
            cout << "    " << "Low to high set" << endl;
            SelectionSort(A5, 1000, comparisons, swaps);
            DisplayComSwaps(comparisons, swaps);
            cout << "    " << "High to low set" << endl;
            SelectionSort(A6, 1000, comparisons, swaps);
            DisplayComSwaps(comparisons, swaps);
            cout << endl;

            // Magnitude: 10000
            cout << "Data set magnitude: 10000" << endl;
            cout << "    "<< "Random set" << endl;
            SelectionSort(A7, 10000, comparisons, swaps);
            DisplayComSwaps(comparisons, swaps);
            cout << "    " << "Low to high set" << endl;
            SelectionSort(A8, 10000, comparisons, swaps);
            DisplayComSwaps(comparisons, swaps);
            cout << "    " << "High to low set" << endl;
            SelectionSort(A9, 10000, comparisons, swaps);
            DisplayComSwaps(comparisons, swaps);  
            cout << endl;         
        }
        // Merge Sort
        else if(i == 1)
        {
            cout << "------------------------";
            cout << "------------------------" << endl;
            cout << "Mergesort:" << endl;
            cout << "------------------------";
            cout << "------------------------" << endl;
            // Magnitude: 100
            cout << "Data set magnitude: 100" << endl;
            cout << "    "<< "Random set" << endl;
            MergeSort(A1, 0, 99, comparisons, swaps, 100);
            DisplayComSwaps(comparisons, swaps);
            cout << "    " << "Low to high set" << endl;
            MergeSort(A2, 0, 99, comparisons, swaps, 100);
            DisplayComSwaps(comparisons, swaps);
            cout << "    " << "High to low set" << endl;
            MergeSort(A3, 0, 99, comparisons, swaps, 100);
            DisplayComSwaps(comparisons, swaps);
            cout << endl;

            // Magnitude: 1000
            cout << "Data set magnitude: 1000" << endl;
            cout << "    "<< "Random set" << endl;
            MergeSort(A4, 0, 999, comparisons, swaps, 1000);
            DisplayComSwaps(comparisons, swaps);
            cout << "    " << "Low to high set" << endl;
            MergeSort(A5, 0, 999, comparisons, swaps, 1000);
            DisplayComSwaps(comparisons, swaps);
            cout << "    " << "High to low set" << endl;
            MergeSort(A6, 0, 999, comparisons, swaps, 1000);
            DisplayComSwaps(comparisons, swaps);
            cout << endl;

            // Magnitude: 10000
            cout << "Data set magnitude: 10000" << endl;
            cout << "    "<< "Random set" << endl;
            MergeSort(A7, 0, 9999, comparisons, swaps, 10000);
            DisplayComSwaps(comparisons, swaps);
            cout << "    " << "Low to high set" << endl;
            MergeSort(A8, 0, 9999, comparisons, swaps, 10000);
            DisplayComSwaps(comparisons, swaps);
            cout << "    " << "High to low set" << endl;
            MergeSort(A9, 0, 9999, comparisons, swaps, 10000);
            DisplayComSwaps(comparisons, swaps);  
            cout << endl;
        }
        // Quick Sort
        else if(i == 2)
        {
            cout << "------------------------";
            cout << "------------------------" << endl;
            cout << "Quicksort:" << endl;
            cout << "------------------------";
            cout << "------------------------" << endl;
            // Magnitude: 100
            cout << "Data set magnitude: 100" << endl;
            cout << "    "<< "Random set" << endl;
            QuickSort(A1, 0, 99, comparisons, swaps);
            DisplayComSwaps(comparisons, swaps);
            cout << "    " << "Low to high set" << endl;
            QuickSort(A2, 0, 99, comparisons, swaps);
            DisplayComSwaps(comparisons, swaps);
            cout << "    " << "High to low set" << endl;
            QuickSort(A3, 0, 99, comparisons, swaps);
            DisplayComSwaps(comparisons, swaps);

            // Magnitude: 1000
            cout << "Data set magnitude: 1000" << endl;
            cout << "    "<< "Random set" << endl;
            QuickSort(A4, 0, 999, comparisons, swaps);
            DisplayComSwaps(comparisons, swaps);
            cout << "    " << "Low to high set" << endl;
            QuickSort(A5, 0, 999, comparisons, swaps);
            DisplayComSwaps(comparisons, swaps);
            cout << "    " << "High to low set" << endl;
            QuickSort(A6, 0, 999, comparisons, swaps);
            DisplayComSwaps(comparisons, swaps);

            // Magnitude: 10000
            cout << "Data set magnitude: 10000" << endl;
            cout << "    "<< "Random set" << endl;
            QuickSort(A7, 0, 9999, comparisons, swaps);
            DisplayComSwaps(comparisons, swaps);
            cout << "    " << "Low to high set" << endl;
            QuickSort(A8, 0, 9999, comparisons, swaps);
            DisplayComSwaps(comparisons, swaps);
            cout << "    " << "High to low set" << endl;
            QuickSort(A9, 0, 9999, comparisons, swaps);
            DisplayComSwaps(comparisons, swaps);  
            cout << endl;
        }       
    }    
}