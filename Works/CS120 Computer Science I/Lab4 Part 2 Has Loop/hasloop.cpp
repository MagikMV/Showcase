/* Miguel Villanueva
 * CS 120 Lab Section 6
 * February 7, 2019
 * Lab Assignment Number 4, Part 2
*/

#include <iostream>
using namespace std;

int main()
{
	int a = 0;
	int b;
	int input = 1;
	int sum = 0;

	cout << "Please enter five different integers: " << endl;
	for (a = 0; input < 6; input++)
	{
		cin >> b;
		sum = sum + b;	
	}
	
	cout << "The sum of your integers is: " << sum << endl;

	return 0;

}
