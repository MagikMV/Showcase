void showProgramHeader();

#include <iostream>
#include <string>
using namespace std;

void userInput(char array[][40]);
void printArray(char array[][40]);
void find(char array[][40], char targetCharacter);

int main()
{
    showProgramHeader();
    char array[30][40];
    char targetCharacter;
    for(int i = 0; i < 30; i++)
    {
        for(int k = 0; k < 40; k++)
        {
            array[i][k] = '-';
        }
    }
    cout << "Please input ten characters into a 30 x 40 array." << endl;
    cout << "First choose the row location, then the column location, and finally the character you wish to input." << endl;
    cout << "Good luck!" << endl << endl;
    userInput(array);
    printArray(array);
    cout << endl << endl << "Now, enter a character you'd like to find in the array: ";
    cin >> targetCharacter;
    find(array, targetCharacter);
}
//***PROGRAM HEADER***
void showProgramHeader()
{
    cout << "Miguel Villanueva \nCS 120 Section 6 \nApril 18, 2019 \nHomework Assignment Number 10 \n" << endl;
}
//***USER INPUT***
void userInput(char array[][40])
{
    int rowLocation;
    int columnLocation;
    for(int i = 0; i < 10; i++)
    {
        cout << "Row location(0-39): ";
        cin >> rowLocation;
        if(rowLocation > 39)
        {
            do
            {
                cout << "Enter a row location between 0 and 39 please: ";
                cin >> rowLocation;
            }
            while(rowLocation > 39);
        }
        cout << "ColumnLocation(0-39): ";
        cin >> columnLocation;
        if(columnLocation > 39)
        {
            do
            {
                cout << "Enter a column location between 0 and 39 please: ";
                cin >> columnLocation;
            }
            while(columnLocation > 39);
        }
        cout << "Character: ";
        cin >> array[rowLocation][columnLocation];
    }
}
//***PRINT ARRAY***
void printArray(char array[][40])
{
    for(int i = 0; i < 30; i++)
    {
        cout << endl;
        for(int k = 0; k < 40; k++)
        {
            cout << array[i][k] << " ";
        }
    }
}
//***FIND FUNCTION***
void find(char array[][40], char targetCharacter)
{
    int result = 0;
    for(int i = 0; i < 30; i++)
    {
        for(int k = 0; k < 40; k++)
        {
            if (array[i][k] == targetCharacter)
            {
                cout << "Your target character: " << targetCharacter << " is located on Row: "  << i << " Column: " << k << endl;
                result += 1;
            }
        }
    }
    if(result == 0)
    {
        cout << "Your target character could not be found." << endl;
    }
}
