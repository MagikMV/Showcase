/* Miguel Villanueva
 * CS 120 Section 6
 * February 12, 2019
 * Homework Number 4
*/

/* The Game of NIM */

#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
	int num_objects = 23;
	int current_player = 1;
	int move;
	int score_0 = 0;
	int score_1 = 0;
	
	cout << "This is the game of NIM\n";
	cout << "Players 1 & 2 will take turns removing one, two, or three objects\n";
	cout << "There are a total of twenty-three objects, and the player to remove the last object loses\n";
	cout << endl;

	do
	{
		if (current_player == 1)
		{
			cout << "Player 1 enter your move (1 - 3): ";
			cin >> move;
			
			while (move < 1 || move > 3 || move > num_objects)
			{
				cout << "Illegal move. \nEnter a new move: ";
				cin >> move;
			}
		}
		else
		{
			do
			{
				move = 1 + rand() % 3;
				
				if (num_objects == 4)
				{
					move = 3;
				}
				if (num_objects == 3)
				{
					move = 2;
				}
				if (num_objects == 2)
				{
					move = 1;
				}	
			}
			while (move < 1 || move > 3 || move > num_objects);
			
			cout << "Computer removed " << move << endl;	
		}
		
		num_objects = num_objects - move;
        	cout << num_objects << " objects remaining. \n";
        	current_player = (current_player + 1) % 2;
		for (int i = 0; i < num_objects; i++)
                {
                        cout << "#";
                }

		if (num_objects > 18)
		{
			cout << endl << "The Commentator: We're off to a great start here\n";
		}
		else if (num_objects > 15)
		{
			cout << endl << "The Commentator: Skillful mind games are underway!\n";
		}
		else if (num_objects > 14)
		{
			cout << endl << "The Commentator: This is a very exciting game!\n";
		}
		else if (num_objects > 12)
		{
			cout << endl << "The Commentator: I'm on the edge of my seat\n";
		}
		else if (num_objects > 11)
		{
			cout << endl << "The Commentator: Wow didn't see that coming\n";
		}
		else if (num_objects > 9)
		{
			cout << endl << "The Commentator: What's gonna happen next?\n";
		}
		else if (num_objects > 8)
		{
			cout << endl << "The Commentator: Things are ramping up!\n";
		}
		else if (num_objects > 7)
		{
			cout << endl << "The Commentator: I can't believe what I am seeing\n";
		}
		else if (num_objects > 4)
		{
			cout << endl << "The Commentator: We're really closing in on the end of the game\n";
		}
		else if (num_objects > 1)
		{
			cout << endl << "The Commentator: This could be the final move of the game if this player ain't dumb!\n";
		}
		else if (num_objects > 0)
		{
			cout << endl << "The Commentator: Remove that object LOSER!!!\n";
		}
		else
		{
			cout << endl << "The Commentator: What a thrilling end!\n";
		}
		
		if (num_objects == 0)
		{
			cout << "Want to play again?\n";
			cout << "Enter 23 if yes, and 0 if no\n";
			cin >> num_objects;

			if (current_player = 0)
			{
				score_0 = score_0 + 1;
			}

			if (current_player = 1)
			{
				score_1 = score_1 +1;
			}	
		}
	}
	while (num_objects > 0);
	
	if (score_1 > score_0)
	{
		cout << endl << "Player " << current_player << " wins!!!\n";
		cout << "ABSOLUTELY NOTHING!\n";
		cout << "Wow wow wow\n";
		cout << "Ya ya ya ya ya ya ya\n";
		cout << "Congratulations to nobody!!!\n";
		cout << "It is only I, the programer\n";
		cout << "Playing all by myself!\n";
		cout << "YAYYYYY!!!\n";
		cout << "Player " << current_player << " won " << score_1 << " to " << score_0 << endl;
	}
	

	
	cin. ignore ();
	cout << "\nPress enter to quit.\n";
	cin. ignore ();

	return 0;
}
