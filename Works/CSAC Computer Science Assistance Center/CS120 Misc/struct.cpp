/* struct.cpp
 *
 * Miguel Villanueva
 * October 21, 2020
 *
 * Program description:
 *   My valiant attempt at coding the CS 120
 *   lab assignment for fun
 */

#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

typedef struct frog
{
    int health;
    //string name;      //  Apparently not supposed to use string
    char name[32];      //  This works as well
    frog initialize()
    {
	frog player;

        health = 100;
        cout << "Enter the name of your frog" << endl;
        cin >> name;

	return player;
    }
    void print(frog player) //  No paramater also works
    {
	cout << "Frog health: " << player.health << endl;
	cout << "Frog name: " << player.name << endl;
    } 
}frog;

//  Uncessary functions to better match assignemnt
frog PogChamp();
void PagChomp(frog player);

int main()
{
    frog player1;
    frog player2;

    cout << "------------------------------" << endl;
    cout << "Plebian 1:" << endl;
    player1 = PogChamp();
    PagChomp(player1);

    cout << endl << "Plebian 2:" << endl;
    player2 = PogChamp();
    PagChomp(player2);
    cout << "------------------------------" << endl;

/*  // ~ Amazing Code Below ~ \\
 
    player1.initialize();
    player1.print(player1);  //  Unnecessary parameter
    player2.initialize();
    player2.print(player2);  //  Unnecessary paramter
*/
    return 0;
}

//  Extra flex part uno
frog PogChamp()
{
    frog player;

    player.health = 100;
    cout << "Enter the name of your frog" << endl;
    cin >> player.name;

    return player;
}

//  Extra flex part dos
void PagChomp(frog player)
{
    cout << "Frog health: " << player.health << endl;
    cout << "Frog name: " << player.name << endl;

}
