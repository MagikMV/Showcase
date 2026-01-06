/* Miguel Villanueva
 * CS 120 Lab Section 6
 * January 31, 2019
 * Lab Assignment Number 3
*/

#include <iostream>
using namespace std;

int main()
{
	if (0){ // Number 1
		cout << "True\n";
	}else{	
		cout << "False\n";
	}

	if (-7){ // Number 2
		cout << "True\n";
	}else{
		cout << "False\n";
	}	
	
	if (-1 + -2){ // Number 3
		cout << "True\n";
	}else{
		cout << "False\n";
	}
	
	if (-7 + 7){ // Number 4
		cout << "True\n";
	}else{
		cout << "False\n";
	}

	cout << (7 < 8) << endl; // Number 5

	cout << (10 > 10) << endl; // Number 6
	
	cout << ((7 < 10) || (7 > 10)) << endl; // Number 7

	cout << ((7 < 10) && (7 > 10)) << endl; // Number 8

	cout << (-5 >= 5) << endl; // Number 9

	cout << ((7 > 10) || (-5 == 5)) << endl; // Number 10

	cout << !(6 == 7) << endl; // Number 11

	cout << ((10 != 11) && (7 > 8)) << endl; // Number 12

	cout << (((7 == 6) || (7 == 7) || (7 == 8))) << endl; // Number 13

	cout << (6 < (8 && 9)) << endl; // Number 14

	cout << (1 == (6 < 8)) << endl; // Number 15

	cout << (0 == (0 || 1)) << endl; // Number 16

	cout << (6 < (5 + 2)) << endl; // Number 17

	if (6 + (5 == 5)){ // Number 18
		cout << "True\n";
	}else{
		cout << "False\n";
	}	

	if ((6 < 7) + (7 >= 5)){ // Number 19
		cout << "True\n";
	}else{
		cout << "False\n";
	}		

	cout << ((0 < 7) - (0 < 7)) << endl; // Number 20

	cout << ((16 && 17) == 33) << endl; // Number 21

	cout << ((16 < 17) < 15) << endl; // Numbber 22

	cout << ((16 || 17) == 17) << endl; //Number 23
	
	return 0;
}

