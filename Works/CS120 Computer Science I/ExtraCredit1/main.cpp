void showProgramHeader();
void Q1(int value[10]);
int Q2(int array[10]);
void Q3();
void Q4_swap(int a, int b);
void Q5_swap_ptr(int a, int b);
void Q6(char UpperCaseToLowerCase);

#include <iostream>
using namespace std;

int main()
{
    int array[10];
    int a = 1;
    int b = 2;
    char UpperCaseToLowerCase = 'A';
    showProgramHeader();
    Q1(array);
    Q2(array);
    Q3();
    Q4_swap(a, b);
    Q5_swap_ptr(a, b);
    Q6(UpperCaseToLowerCase);
}
//***SHOW PROGRAM HEADER***
void showProgramHeader()
{
    cout << "Miguel Villanueva \nCS 120 Section 6 \nApril 21, 2019 \nHomework Extra Credit Number 1 \n" << endl;
}
//***QUESTION ONE***
void Q1(int value[10])
{
    cout << "Enter ten integers with values between 1 and 8: " << endl;
    for(int i = 0; i < 10; i++)
    {
        cin >> value[i];
        if (value[i] < 1 || value[i] > 8)
        {
            do
            {
                cout << "Invalid input. Enter an integer between 1 and 8: " << endl;
                cin >> value[i];
            }
            while(value[i] < 1 || value[i] > 8);
        }
    }
}
//***QUESTION TWO***
int Q2(int array[10])
{
    int sum = 0;
    int minimum = array[0];
    int largest = array[0];
    double average;
    for(int i = 0; i < 10; i++)
    {
        sum += array[i];
        if(array[i] < minimum)
        {
            minimum = array[i];
        }
        if(array[i] > largest)
        {
            largest = array[i];
        }
    }
    average = sum / 10.0;
    return largest;
}
//***QUESTION THREE***
void Q3()
{
    for(int i = 1; i <= 10; i++)
    {
        cout << endl;
        for(int k = 1; k <= 10; k++)
        {
            cout << i * k << " ";
        }
    }
    cout << "\n" << endl;
}
//***QUESTION FOUR***
void Q4_swap(int a, int b)
{
    int temp = b;
    b = a;
    a = temp;
}
//***QUESTION FIVE***
void Q5_swap_ptr(int a, int b)
{
    int *ptr_1, *ptr_2, *ptr_3;
    ptr_1 = &a;
    ptr_2 = &b;
    ptr_3 = new int;
    *ptr_3 = a;
    *ptr_1 = b;
    *ptr_2 = *ptr_3;
}
//***QUESTION SIX***
void Q6(char UpperCaseToLowerCase)
{
    UpperCaseToLowerCase += 32;
}
