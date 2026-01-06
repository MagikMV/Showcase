void showProgramHeader();
void printLargeSmall(int number[], int arraySize); // Function that finds the largest and smallest element within the array
void printShiftElements(int number[], int arraySize); // Function that shifts elements

#include <iostream>

using namespace std;

int main()
{
    showProgramHeader();

    int number[10];
    int sum = 0;
    double average;

    cout << "Input ten integer values." << endl;
    for (int i = 0; i < 10; i++) // Loop for integers entered by user
    {
        cout << "Integer: ";
        cin >> number[i];
        sum = sum + number[i];
    }

    cout << endl << "Array: ";
    for (int j = 0; j < 10; j++) // Loop to print out the array
    {
        cout << number[j] << " ";
    }

    average = sum / 10.0;

    cout << endl << "Sum of array: " << sum << endl;
    cout << "Average of array: " << average << endl;
    //***Part 2 of exercise 9.1, commented out for fluidity***
    // cout << endl << "The 11th element of the array: " << number[10] << endl;
    //***Part 3 of exercise 9.2, commented out for fluidity***
    // cout << endl << "The 10,000th element of the array: " << number[9999] << endl;

    printLargeSmall(number, 10);
    printShiftElements(number, 10);
}

void showProgramHeader()
{
    cout << "Miguel Villanueva \nCS 120 Lab Section 6 \nLab Assignment Number 9 \nMarch 20, 2019\n" << endl;
}

void printLargeSmall(int number[], int arraySize)
{
    double largestElement = number[0];
    double smallestElement = number[0];

    for (int i = 0; i < arraySize; i++)
    {
        if(number[i] > largestElement) largestElement = number[i];
    }
    for (int j = 0; j << arraySize; j++)
    {
        if(number[j] < smallestElement) smallestElement = number[j];
    }

    cout << endl << "Largest element in array: " << largestElement << endl;
    cout << "Smallest element in array: " << smallestElement << endl;
 }

 void printShiftElements(int number[], int arraySize)
 {
     int temp1 = number[0]; // Original code "int temp = number[0];"
     int temp2 = number[1]; // Original code "not included"

     for (int i = 2; i < arraySize; i++)
     {
         number[i-2] = number[i]; // Original code "number[i-1] = number[i];"
     }
     number[arraySize-1] = temp2; // Original code "number[arraySize-1] = temp;"
     number[arraySize-2] = temp1; // Original code "not included"

     cout << endl << "Shifted Array: ";
     for (int j = 0; j < arraySize; j++)
     {
         cout << number[j] << " ";
     }
 }
