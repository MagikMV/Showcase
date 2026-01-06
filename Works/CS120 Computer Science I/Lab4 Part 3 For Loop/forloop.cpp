/* Miguel Villanueva
 * CS 120 Lab Section 6
 * February 7, 2019
 * Lab Assignment Number 4, Part 3
*/

#include <iostream>
using namespace std;

int main()
{
	int a = 0;
	int b;
	int input = 1;
	int sum;
	
	cout << "Please enter up to 100 integers: " << endl;
	cout << "If you wish to exit, enter 0." << endl;

	for (a = 0; input < 101; input++)
	{
		cin >> b;
		sum = sum + b;

		if (b == 0)
		{
			break;
		}
	}

	cout << "The sum of your integers is: " << sum << endl;

	return 0;
}
