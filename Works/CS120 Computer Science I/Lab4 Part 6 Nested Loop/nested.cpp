/* Miguel Villanueva
 * CS 120 Lab Section 6
 * February 7, 2019
 * Lab Assignment Number 4, Part 6
*/

#include <iostream>
using namespace std;

int main()
{
	int x = 40;
	int y = 0;
	int z = 0;

	cout << endl; // Spacing to see the program in all it's glory
	cout << "    "; // Space for x axis

	for (z = 0; z < 10; z++) // Loop for x axis
	{
		cout << z << "  ";
	}
	
	for (x = 40; x <= 110; x = x + 10)
	{
		cout << "\n"; // Makes y axis
		cout << x << " ";
		
		if (x < 100)
		{
			cout << " ";
		}
			
		for (y = 0; y < 10; y++)
		{
				cout << static_cast <char> (x + y) << "  "; // Ascii characters
		}	
	
	}
	
	cout << endl << endl << "Did I do it?" << endl; // Extra Spacing
	cout << "FINALLY, good job, I win de game." << endl << endl; // Spacing to feel good about myself 

	return 0;
}

