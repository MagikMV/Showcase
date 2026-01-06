/* Miguel Villanueva
 * CS 120 Lab Section 6
 * February 20, 2019
 * Lab Assignment Number 6
*/

#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
	/* GAME MENU */
	
	int game = 1; // Variable that decides which mini game the user wishes to play
	int wins = 0; // Variable that tracks amount of wins across all games played
	int played = 0; // Number of games played by the user

	while (game > 0)
	{
		cout << "If you wish to play mini game one, press 1" << endl;
		cout << "If you wish to play mini game two, press 2" << endl;
		cout << "OR, if you wish to exit before or after a game, press 0" << endl;
		cin >> game;

		switch (game)
		{
			case 0:  
				cout << endl << "You decided to exit" << endl;
				break;
			case 1: 
				cout << endl << "You chose mini game one" << endl;
				break;
			case 2: 
				cout << endl << "You chose mini game two" << endl;
				break;
			
			default:
				cout << endl << "Whoops, you entered an unknown command" << endl;
				cout << "Guess you'll be playing mini game one" << endl; 
		}
		
		/* MINI GAME ONE */
		
		if (game == 1 || game >= 3)
		{
			int a;
			int b;
			int product = 0;
			int calculation;

						
		}
		
		/* MINI GAME TWO */

		if (game == 2)
		{

		}
	}
	
	/* GAMES WON */
	
	if (game == 0)
	{
		cout << endl << "You won " << wins << " out of " << played << " games" << endl;
		cout << "Great going! Hope you had fun!" << endl;
	}
	
	return 0;
}
