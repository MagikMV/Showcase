/* Miguel Villanueva
 * CS 120 Lab Section 6
 * Februrary 20, 2019
 * Lab Assignment Number 6
*/

#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
	/* GAME MENU */
		
	int game = 1;
	int wins = 0; // Total amount of wins
	int played = 0; // Games played
	double success;
	
	while (game > 0)
	{
		cout << endl << "If you wish to play the Random Number Guessing Game, press 1" << endl;
		cout << "If you wish to play Rock, Paper, Scissors, press 2" << endl;
		cout << "If you wish to play Calculate The Sum, press 3" << endl;
		cout << "If you wish to play Calculate The Product, press 4" << endl; // New game
		cout << "If you wish to play Calculate The Difference, press 5" << endl; // New Game
		cout << "OR, if you wish to exit before or after a game, press 0" << endl;
		cin >> game;
	
		switch (game)
		{
			case 0:
				cout << endl << "You have decided to exit" << endl;
				break;
			case 1:
				cout << endl << "You chose the Random Number Guessing Game" << endl;
				break;
			case 2:
				cout << endl << "You chose Rock, Papaer, Scissors" << endl;
				break;
			case 3:
				cout << endl << "You chose Calculate The Sum" << endl;
				break;
			case 4:
				cout << endl << "You chose Calculate The Product" << endl; // New Game
				break;
			case 5:
				cout << endl << "You chose Calculate The Difference" << endl; // New Game
				break;
			default: 
				cout << endl << "Whoops, you entered an unknown command" << endl;
				cout << "Guess you'll be playing the Random Number Guessing Game!" << endl;
				break;
		}

		/* RANDOM NUMBER GUESSING GAME */

		if (game == 1 || game >= 6)
		{
			int random; // The so called random number
			int guess; // The guess of the user
			int tries = 7;
	
			cout << "Guess a random number from 1 - 100" << endl;
			cout << "You have seven tries!" << endl;	
			random = rand() % 100 + 1;	

			while (tries > 0)
			{ 
				cin >> guess;		
				if (guess >= 1 && guess <= 100)
				{
					if (guess == random || random == guess)
					{
						cout << "Great guessing!" << endl;
						tries = tries - 1;
						cout << "You had " << tries << " tries remaining" << endl;
						break;
					}
					else if (guess < random)
					{
						cout << "A little low! Guess higher!" << endl;
						tries = tries - 1;
						cout << "You have " << tries << " tries remaining" << endl;
					}
					else if (guess > random)
					{
						cout << "A little high! Guess lower!" << endl;
						tries = tries - 1;
						cout << "You have " << tries << " tries remaining" << endl;
					}
				}
				else
				{
					cout << "Invalid number" << endl;
					cout << "Enter a number from 1 -100" << endl;
					tries = tries - 0;
					cout << "You still have " << tries << " tries remaining" << endl;
				}
			}

			cout << "The random number was: " << random << endl;
			if (guess != random)
			{
				cout << "You lose the Random Number Game" << endl;
				played = played + 1;
			}
			else
			{
				cout << "You win the Random Number Game" << endl;
				wins = wins + 1;
				played = played + 1;
			}
		
			cout << endl << "Enter 1 to return to game menu" << endl;
			cout << "Enter 0 to exit" << endl;
			cin >> game;
		}	

		/* ROCK, PAPER, SCISSORS */

		if (game == 2)	
		{
			int movea; // Move of Player 1
			int moveb; // Move of Player 2 or the computer
			int setsa = 0; // Points of Player 1
			int setsb = 0; // Points of Player 2
			int rounds = 3;

			cout << "Enter the number 1 for Rock" << endl;
			cout << "Enter the number 2 for Paper" << endl;
			cout << "Enter the number 3 for Scissors" << endl;
			cout << "First player with two points wins!" << endl;
	
	
			while (rounds > 0)
			{
				moveb = rand() % 3 + 1;
				cin >> movea;
				if (movea >= 1 && movea <= 3)
				{
					if (movea == 1 && moveb == 3)
					{
						cout << "Player 1" << "'" << "s move: Rock" << endl;
						cout << "Player 2" << "'" << "s move: Scissors" << endl;
						cout << "Rock beats Scissors" << endl;
						cout << "Point to Player 1" << endl; 
						setsa = setsa + 1;
						rounds--;			
					}
					if (movea == 2 && moveb == 1)
					{
						cout << "Player 1" << "'" << "s move: Paper" << endl;
						cout << "Player 2" << "'" << "s move: Rock" << endl;
						cout << "Paper beats Rock" << endl;
						cout << "Point to Player 1" << endl;
						setsa = setsa + 1;
						rounds--;
					}
					if (movea == 3 && moveb == 2)
					{
						cout << "Player 1" << "'" << "s move: Scissors" << endl;
						cout << "Player 2" << "'" << "s move: Paper" << endl;
						cout << "Scissors beats Paper" << endl;
						cout << "Point to Player 1" << endl;
						setsa = setsa + 1;
						rounds--;
					}
					if (moveb == 1 && movea == 3)
					{
						cout << "Player 1" << "'" << "s move: Scissors" << endl;
						cout << "Player 2" << "'" << "s move: Rock" << endl;
						cout << "Rock beats Scissors" << endl;
						cout << "Point to Player 2" << endl;
						setsb = setsb + 1;
						rounds--;
					}
					if (moveb == 2 && movea == 1)
					{
						cout << "Player 1" << "'" << "s move: Rock" << endl;
						cout << "Player 2" << "'" << "s move: Paper" << endl;
						cout << "Paper beats Rock" << endl;
						cout << "Point to Player 2" << endl;
						setsb = setsb + 1;
						rounds--;
					}
					if (moveb == 3 && movea == 2)
					{
						cout << "Player 1" << "'" << "s move: Paper" << endl;
						cout << "Player 2" << "'" << "s move: Scissors" << endl; 
						cout << "Scissors beats Paper" << endl;
						cout << "Point to Player 2" << endl;
						setsb = setsb + 1;
						rounds--;
					}
					if (movea == moveb)
					{
						cout << "Oops, same move, replay the round!" << endl;
						rounds = rounds + 1;
					}
				}
				else
				{
					cout << "Move unknown" << endl;
					cout << "Enter 1, 2, or 3" << endl;
					rounds + 1;
				}
		
				if (setsa == 2)
				{
					cout << "Player 1 won Rock, Paper, Scissors with " << rounds << " rounds remaining!" << endl;
					wins = wins + 1;
					played = played + 1;
					break;
				}
				if (setsb == 2)
				{
					cout << "Player 2 won Rock, Paper, Scissors with " << rounds << " rounds remaining!" << endl;
					played = played + 1;
					break;
				}
			}
		
			cout << endl << "Enter 1 to return to the menu" << endl;
			cout << "Enter 0 to exit" << endl;
			cin >> game;
		}

		/* CALCULATE THE SUM */

		if (game == 3)
		{
			int a;
			int b;
			int sum = 0;
			int calculation; // Calculation of the user
	
			a = rand() % 50 + 1;
			b = rand() % 50 + 1;

			sum = a + b;
			cout << "What is " << a << " plus " << b << endl;
			cin >> calculation;
	
			if (calculation == sum)
			{
				cout << "That's correct!" << endl;
				cout << "You won Calculate The Sum!" << endl;
				wins = wins + 1;
				played = played + 1;
			}
			else
			{
				cout << "Eeeaghr, Wrong!" << endl;
				cout << "Incorrect, Sharpin' Up!" << endl;
				played = played + 1;
			}
		
			cout << endl << "Enter 1 to return to the menu" << endl;
                	cout << "Enter 0 to exit" << endl;
			cin >> game;
		}
		
		/* CALCULATE THE PRODUCT */
		
                if (game == 4)
                {
                        int c;
                        int d;
                        int product = 0;
                        int answer;

                        c = rand() % 12 + 1;
                        d = rand() % 12 + 1;

                        product = c * d;
                        cout << "What is " << c << " multiplied by " << d << endl;
                        cin >> answer;

                        if (answer == product)
                        {
                                cout << "Awesome work!" << endl;
                                cout << "You won Calculate The Product!" << endl;
                                wins = wins + 1;
                                played = played + 1;
                        }
                        else
                        {
                                cout << "Nope!" << endl;
                                cout << "Incorrect, you played yourself!" << endl;
                                played = played + 1;
                        }

                        cout << endl << "Enter 1 to return to the menu" << endl;
                        cout << "Enter 0 to exit" << endl;
                        cin >> game;
                }
		
		/* CALCULATE THE DIFFERENCE */

		
                if (game == 5)
                {
                        int e;
                        int f;
                        int difference = 0;
                        int solution;

                        e = rand() % 100 + 1;
                        f = rand() % 100 + 1;

                        difference = e - f;
                        cout << "What is " << e << " minus " << f << endl;
                        cin >> solution;

                        if (solution == difference)
                        {
                                cout << "Wow! Amazing!" << endl;
                                cout << "You won Calculate The Difference!" << endl;
                                wins = wins + 1;
                                played = played + 1;
                        }
                        else
                        {
                                cout << "Are you serious!" << endl;
                                cout << "Incorrect, this should be easy!" << endl;
                                played = played + 1;
                        }

                        cout << endl << "Enter 1 to return to the menu" << endl;
                        cout << "Enter 0 to exit" << endl;
                        cin >> game;
                }

	}

	/* GAMES WON */	
	
	success = (wins * 1.0) / (played * 1.0);
	success = success * 100;	

	if (game == 0)
	{
		cout << endl << "You won " << wins << " out of " << played << " games" <<  endl;
		cout << "Your success rate was " << success << "%" << endl; 
		
		if (success >= 90)
		{
			cout << "Woah! Crazy sucess rate, great job!" << endl;
		}
		else if (success >= 70)
		{
			cout << "Your above average! Keep it up!" << endl;
		}
		else if (success >= 40)
		{
			cout << "You could proabably do better, but great effort!" << endl;
		}
		else
		{
			cout << "Good start, but keep on practicing!" << endl;
		}
	}

	return 0;

}
