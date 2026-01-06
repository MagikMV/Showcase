/* Miguel Villanueva
 * CS 120 Lab Section 6
 * January 24, 2019
 * Lab Assignment Number 2
*/

#include <iostream>
using namespace std;

int main()
{
	int feet;
	int inches;

	cout << "This is a program that estimates your ideal body weight based on your height" << endl << endl;
	cout << "Please enter your height: feet and inches separately" << endl << endl;
	cout << "How many feet?" << endl;
	cin >> feet;
	cout << "How many inches?" << endl;
	cin >> inches;

	float centi = (feet * 30.48) + (inches * 2.54); // centi meaning height in centimeters

	cout << endl << "You are " << feet << "\"" << inches << "\'" << " or " << centi << " centimeters" << endl;
	
	int weight = (feet - 5) * 60 + (inches * 5) + 110; // weight in pounds
	double kilo = weight * 0.4536; // kilo meaning weight in kilograms

	cout << "And your ideal body weight is " << weight << " pounds or " << kilo << " kilograms" << endl << endl;
}
