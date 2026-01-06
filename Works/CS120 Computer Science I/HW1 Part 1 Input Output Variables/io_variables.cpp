/* Miguel Villanueva
 * CS 120 Section 6
 * January 23, 2019
 * Homework Number 1, Exercise 1.1
*/

#include<iostream>
using namespace std;

int main()
{
	float x, y; // previous variable type int
	float sum = 0, average; // previous variable type int

	cout << "Please enter a number: " << flush;
	cin >> x;
	cout << "Please enter another number: " << flush;
	cin >> y;
	sum = x + y;
	cout << "The sum of " << x << " plus " << y;
	cout << " is " << sum << ". "; // added space after period for a cleaner sentence
	average = sum/2;
	cout << "The average of your number is ";
	cout << average << "." << endl;

	return 0;
}
