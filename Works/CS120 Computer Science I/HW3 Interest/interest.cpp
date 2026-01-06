/* Miguel Villanueva
 * CS 120 Section 6
 * February 5, 2019
 * Homework Number 3
*/

#include <iostream>
#include <math.h>

using namespace std;

int main()
{
	int year = 1;
	double bob;
	double alice;
	double interest_a; // interest of alice
	double interest_b = 0.03; // interest of bob
	double investment_a; // balance of alice
	double investment_b; // balance of bob

	cout << "Alice, please enter your investment amount: ";
	cin >> alice;
	
	if (alice < 1){
		alice = 1;
	}
	
	bob = alice;
	cout << "Alice" << "'" << "s original investment: " << alice << endl;
	cout << "Bob" << "'" << "s original investment: " << bob << endl;


	if (alice < 100){
		interest_a = 0.07;
	}
	else if (alice < 300){
		interest_a = 0.08;
	}
	else if (alice < 500){
		interest_a = 0.09;
	}
	else if (alice < 1000){
		interest_a = 0.10;
	}
	else{
		interest_a = 0.11;
	}

	cout << "Alice" << "'" << "s interest rate: " << interest_a << endl;
	cout << "Bob" << "'" << "s interest rate: " << interest_b << endl;

	cout << investment_c << endl;	

	investment_a = alice + (alice * interest_a);
	investment_b = bob + (bob * interest_b);
	
	do
	{
		investment_a = (investment_a + (alice * interest_a));
		investment_b = (investment_b + (investment_b * interest_b));
		year++;
	}
	while (investment_b <= investment_a);

	cout << "Years until Bob" << "'" << "s investment will exceed Alice" << "'" << "s: " << year << endl;
	cout << "Alice" << "'" << "s investment at this time will be: " << investment_a << endl;
	cout << "Bob" << "'" << "s investment at this time will be: " << investment_b << endl;

	return 0;
}
