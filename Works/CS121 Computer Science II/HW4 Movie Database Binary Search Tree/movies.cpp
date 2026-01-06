/* movies.cpp
 *
 * CS 121 Bolden
 * Miguel Villanueva  //  vill9577@vandals.uidaho.edu
 * November 13, 2019
 *
 * Eluktronics P65_67HSHP  //  Intel Core i7-7700HQ
 * GCC 5.1.0
 *
 * Program Description:
 *      Displays information from a movie data base
 */

#include <iostream>
#include <fstream>
#include <string>
#include "BSTree.cpp"

using namespace std;

int main()
{
    string line;
    BST tree;

    ifstream infile;
    infile.open("movies.txt");

    while(getline(infile, line))
    {
        string title;
        string year;
        string actors[32];
        if(line.empty())
        {
            continue;
        }
        int length = line.find_last_of( "(" );
        title = line.substr( 0, length);
        year = line.substr( length + 1, 4);

        int Count = 0;
        while( getline(infile, line) && Count < 32)
        {
            if(line.empty())
            {
                break;
            }
            else
            {
                actors[Count] = line;
                Count++;
            }
        }
        tree.AddNode(title, year, actors);
    }
    infile.close();

    cout << "All movie titles in alphabetical order:" << endl;
    tree.DisplayTitles();

    cout << endl << "Blazing Saddles Actors:" << endl;
    tree.DisplayActors("Blazing Saddles ");

    cout << endl << "Silent Running Actors:" << endl;
    tree.DisplayActors("Silent Running ");

    cout << endl << "The Running Man Actors:" << endl;
    tree.DisplayActors("The Running Man ");

    cout << endl << "Conan the Destroyer Actors:" << endl;
    tree.DisplayActors("Conan the Destroyer ");

    cout << endl << "Conan the Barbarian Actors:" << endl;
    tree.DisplayActors("Conan the Barbarian ");

    cout << endl << "Tom Cruise Movies:" << endl;
    tree.DisplayActorsTitles("Tom Cruise");

    cout << endl << "Carrie Fisher Movies:" << endl;
    tree.DisplayActorsTitles("Carrie Fisher");

    cout << endl << "Roger Moore Movies:" << endl;
    tree.DisplayActorsTitles("Roger Moore");

    cout << endl << "Arnold Schwarzenegger Movies:" << endl;
    tree.DisplayActorsTitles("Arnold Schwarzenegger");

    cout << endl << "Tom Hanks Movies:" << endl;
    tree.DisplayActorsTitles("Tom Hanks");

    cout << endl << "1975 Releases:" << endl;
    tree.DisplayYearsTitles("1975");

    cout << endl << "1984 Releases:" << endl;
    tree.DisplayYearsTitles("1984");
}
