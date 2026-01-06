#include <iostream>
using namespace std;

int inputrange(int min, int max)
{
    int n;
    cout << "Enter in a number between " << min << " and " << max << endl;
    cin >> n;

    while(!(n >= min && n <= max))
    {
	    cout << "ERROR: Enter in a number between " << min << " and " << max << endl;
    	cin >> n;
    }
    return n;
}

int main()
{
    int number;
    int max = 0;
    //int rangeNum = inputrange(1, 10);
    if(1 % 2)
	    cout << "That's awesome" << endl;

    cout << 2 * 5.5 + 20 / 3 + 2 << endl;
    cout << "============================================" << endl;
    cout << "       Enter 10 different integers" << endl;
    cout << "I will tell you the largest of those numbers" << endl;

    cout << "> ";
    cin >> number;
    max = number;
    for(int i = 0; i < 9; i++)
    {
	    cout << "> ";
	    cin >> number;
	if (number > max)
	    max = number;
    }

    cout << "The max value you entered is: " << max << endl;
    cout << "============================================" << endl;
}
