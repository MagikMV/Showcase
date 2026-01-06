void ProgramHeader();
double f_WindChill(double temp, double mph); // Wind chill in fahrenheit
double c_WindChill(double doesntmatter); // Wind chill in celsius

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	ProgramHeader();
	
	double temp, mph; // Temperature, Wind Speed (MPH)
	double f, c; // Fahrenheit, Celsius; 	
 
	cout << endl << "Enter the temperature (Fahrenheit)" << endl;
	cin >> temp;

	cout << "Enter the wind speed (MPH)" << endl;
	cin >> mph;

	cout << "Temperature: " << temp << " degrees Fahrenheit" << endl;
	cout << "Wind Speed: " << mph << " Miles Per Hour" << endl; 
	
	f = f_WindChill(temp, mph); // Function call
 	c = c_WindChill(f); // Function call
}

void ProgramHeader()
{
	cout << "Miguel Villanueva" << endl;
        cout << "CS 120 Section 6" << endl;
        cout << "February 26, 2019" << endl;
        cout << "Homework Number 6" << endl;
}

double f_WindChill(double temp, double mph)
{
	double windchill = 35.74 + (0.6215 * temp) - pow(35.75 * mph, 0.16) + pow(0.4275 * temp * mph, 0.16);
	cout << "The wind chill in Fahrenheit is: " << windchill << endl;
	return (windchill);
}

double c_WindChill(double doesntmatter) // Arbitrary parameter
{
	double celsius = (doesntmatter - 32) * (5/9.0);
	cout << "And the wind chill in Celsius is: " << celsius << endl;
}


