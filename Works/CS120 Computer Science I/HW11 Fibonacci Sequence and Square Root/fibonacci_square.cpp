void showProgramHeader();
int fib(int number);
float squareRoot(float number, float estimate, float tolerance);

#include <iostream>
using namespace std;

int main()
{
    int fibNumber; // Element of the Fibonacci Sequence that the user wants to know
    float number; // Number that the user wants to know the square root of
    float estimate; // User estimate of number
    float tolerance = 0.001;
    showProgramHeader();
    cout << "Enter the element(number in the series from zero) of the Fibonacci Sequence you want to know: ";
    cin >> fibNumber;
    cout << "Element value: " << fib(fibNumber) << endl;
    cout << endl << "Next, enter a number you'd like to know the square root of, followed by your estimate of the square root." << endl;
    cout << "Number: ";
    cin >> number;
    cout << "Estimate: ";
    cin >> estimate;
    cout << "Square root: " << squareRoot(number, estimate, tolerance);

    return 0;
}
//***PROGRAM HEADER***
void showProgramHeader()
{
    cout << "Miguel VIllanueva \nCS 120 Section 6 \nApril 25, 2019 \nHomework Number 11 \n" << endl;
}
//***FIBONACCI SEQUENCE FUNCTION***
int fib(int number)
{
    if(number == 0)
        return 0;
    if(number == 1)
        return 1;
    if(number > 1)
        return fib(number - 1) + fib(number - 2);

    return 0;
}
//***SQUARE ROOT FUNCTION***
float squareRoot(float number, float estimate, float tolerance)
{
    if(((estimate * estimate) - number) <= tolerance)
        return estimate;
    if(((estimate * estimate) - number) > tolerance)
        return squareRoot(number, ((estimate * estimate) + number) / (2 * estimate), tolerance);

    return 0;
}
