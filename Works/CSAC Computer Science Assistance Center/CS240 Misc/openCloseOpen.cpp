/* openCloseOpen.cpp
 *
 * Miguel Villanueva
 * CSAC
 * May 11, 2021
 */

#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    string whale[4];
    ifstream yehaw;
    yehaw.open("fish.txt");

    yehaw >> whale[0];
    yehaw >> whale[1];

    yehaw.close();
    yehaw.open("fish.txt");
    
    yehaw >> whale[2];
    yehaw >> whale[3];

    yehaw.close();

    for(int i = 0; i < 4; i++)
	    cout << whale[i] << " ";
    cout << endl;

    return 0;
}
