/* Miguel Villanueva
 * CS 120 Lab Section 6
 * February 7, 2019
 * Lab Assignment 4, Part 5
*/

#include <iostream>
using namespace std;

int main()
{
	int a;
	int input = 1;
	int sum = 0;

	cout << "Please enter up to 100 integers: " << endl;
	cout << "If you wish to exit, enter 0" << endl;
	do
	{
		cin >> a;
		sum = sum + a;
		if (a == 0)
		{
			break;
		}

	} while (input < 101);
	
	cout << "The sum of your integers is: " << sum << endl;

	return 0;
}
