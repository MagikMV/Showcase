void ProgramHeader ();
int NaturalNumber (int a);
int ProductCalculation (int b, int c);
int PrintCalculation (int d);

#include <iostream>

using namespace std;

int main ()
{
	ProgramHeader ();
	int a, b, c, d;
	b = NaturalNumber (a);
	c = NaturalNumber (a);
	d = ProductCalculation (b, c);
	PrintCalculation (d);
}

void ProgramHeader ()
{
	cout << "Miguel Villanueva" << endl;
	cout << "CS 120 Lab Section 6" << endl;
	cout << "February 27, 2019" << endl;
	cout << "Lab Assignment Number 7" << endl;
}

int NaturalNumber (int a)
{
	cout << "Enter a nautral number (an integer larger than zero) " << endl;
	cin >> a;
	while (a <= 0)
	{		
		cout << "Please enter an integer larger than zero" << endl;
		cin >> a;
	}
	return a;
}

int ProductCalculation (int b, int c)
{
	return (b * c);
}

int PrintCalculation (int d)
{
	cout << "The product of the two natural numbers is: " << d << endl;
}
