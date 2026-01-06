/* Miguel Villanueva
 * CS 120 Lab Section 6
 * February 7, 2019
 * Lab Assignment Number 4, Part 1
*/

#include <iostream>
using namespace std;

int main()
{
	int a, b, c, d, e;
	int sum = 0;

	cout << "Please enter five different integers: " << endl;
	cin >> a;
	cin >> b;
	cin >> c;
	cin >> d;
	cin >> e;

	sum = a + b + c + d + e;
	cout << "The sum of your integers is: " << sum << endl;
		
	return 0;
}
