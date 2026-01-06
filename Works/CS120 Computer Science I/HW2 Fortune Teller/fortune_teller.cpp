/* Miguel Villanueva
 * CS 120 Section 6
 * January 30, 2019
 * Homework Number 2

	/* The Fortune Teller -
	 * a simple program introducing some
	 * fundamental programming concepts.
	 */

#include <iostream>
using namespace std;

int main()
{
	int favorite;
	int disliked;
	int random;
	int interesting;
	int lucky;

	cout << "Ready to recieve your fortune?" << endl << endl;
	cout << "Enter your favorite number (no decimals): ";
	cin >> favorite;
	cout << "Enter a number you don't like (no decimals): ";
	cin >> disliked;
	cout << "Enter a random number (no decimals): ";
	cin >> random;
	cout << "Finally, enter a number that is interesting to you (no decimals): ";
	cin >> interesting;

	lucky = (favorite * disliked * random / interesting) % 10;
	cout << endl << "Your secret, lucky number is: " << lucky << endl;
	
	if (lucky < 0)
	{
		cout << "Try to be less negative." << endl;
	}
	if (lucky >= 0 && lucky < 3)
	{
		cout << "Think bigger!" << endl;
	}
	if (lucky >= 3 && lucky < 5)
	{
		cout << "Today you should embrace technology." << endl;
	}
	if (lucky >= 5 && lucky < 7)
	{
		cout << "Today you may find fortune, but only if you seek earnestly!" << endl;
	}
	if (lucky >= 7 && lucky < 9)
	{
		cout << "You may meet a special someone today, look closely." << endl;
	}
	if (lucky == 9)
	{
		cout << "Today is your lucky day!" << endl;
	}

	cin.ignore();
	cout << endl << "Please enter to quit." << endl; // Added an extra line for a cleaner look
	cin.ignore();
	return 0;
}
