void showProgramHeader();
void reverse(int array_1[], int arrayLength); // Question #1
void rotate(double *ptrA, double *ptrB, double *ptrC); //Question #3

#include <iostream>
using namespace std;
//***QUESTION 2: SOLID CLASS***
class solid
{
    private:
        double height, width, length;
    public:
        solid();
        double volume();
        void set_height(double value);
        int is_cube();
};
//***QUESTION 4: NODE CLASS***
class node
{
    public:
        string name;
        node *next;
        node();
        void print();
};
//***QUESTION 4: GLOBAL VARIABLE HEADER POINTER***
node *head = NULL;

int main()
{
    showProgramHeader();
    // QUESTION 1
    int arrayLength = 4;
    int array1[arrayLength] = {1, 2, 3, 4};
    cout << "***QUESTION 1***\n";
    for(int i = 0; i < arrayLength; i++)
    {
        cout << array1[i] << " ";
    }
    cout << endl;
    reverse(array1, arrayLength);
    // QUESTION 3
    cout << "***QUESTION 3***\n";
    double a = 3.4, b = 12.3, c = 7.9;
    double *ptrA = &a, *ptrB = &b, *ptrC = &c;
    cout << *ptrA << " " << *ptrB << " " << *ptrC << endl;
    rotate(ptrA, ptrB, ptrC);
    cout << *ptrA << " " << *ptrB << " " << *ptrC << endl;
    // QUESTION 4
    cout << "***QUESTION 4***\n";
    node *ptrX, *ptrY, *ptrZ;
    ptrX = new node;
    ptrY = new node;
    ptrZ = new node;
    ptrX->next = ptrY;
    ptrY->next = ptrZ;
    head = ptrX;
    head->print();
}
//***PROGRAM HEADER***
void showProgramHeader()
{
    cout << "Miguel Villanueva \nCS 120 Section 6 \nMay 1, 2019 \nHomework Extra Credit Number 2\n" << endl;
}
//***QUESTION 1: REVERSE FUNCTION***
void reverse(int array_1[], int arrayLength)
{
    int temp[arrayLength];
    for(int i = 0; i < arrayLength; i++)
    {
        temp[arrayLength - 1 - i] = array_1[i];
    }
    for(int i = 0; i < arrayLength; i++)
    {
        array_1[i] = temp[i];
        cout << array_1[i] << " ";
    }
    cout << endl;
}
//***QUESTION 2: SOLID CONSTRUCTOR***
solid::solid()
{
    height = 0;
    width = 0;
    length = 0;
}
//***QUESTION 2: VOLUME MEMBER FUNCTION***
double solid::volume()
{
    return height * width * length;
}
//***QUESTION 2: SET HIEGHT MEMBER FUNCTION***
void solid::set_height(double value)
{
    if(value > 0)
        height = value;
    if(value < 0)
        cout << "Error, invalid height." << endl;
}
//***QUESTION 2: IS CUBE MEMBER FUNCTION***
int solid::is_cube()
{
    if(height == width && length == width && height == length)
        return 1;
    else
        return 0;
}
//***QUESTION 3: ROTATE FUNCTION***
void rotate(double *ptrA, double *ptrB, double *ptrC)
{
    double *temp = new double;
    *temp = *ptrA;
    *ptrA = *ptrB;
    *ptrB = *ptrC;
    *ptrC = *temp;
}
//***QUESTION 4: NODE CONSTRUCTOR***
node::node()
{
    cout << "Enter a name(one word): ";
    cin >> name;
    next = NULL;
}
//***QUESTIOn 4: PRINT MEMBER FUNCTION***
void node::print()
{
    node *temp = head;
    node *previous1;
    node *previous2;
    if(head == NULL)
    {
        cout << "Empty list!" << endl;
    }
    else
    {
        cout << temp->name << " ";
        while(temp->next != NULL)
        {
            previous2 = previous1;
            previous1 = temp;
            temp = temp->next;
            cout << temp->name << " ";
        }
    }
    cout << endl << temp->name << " " << previous1->name << " " << previous2->name;
}
