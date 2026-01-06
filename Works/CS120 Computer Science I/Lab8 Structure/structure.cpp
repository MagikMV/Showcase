void showProgramHeader();

#include <iostream>
using namespace std;

//***Character Structure***

typedef struct character
{
	char character_name[50];
	int character_age;
	int character_weight;
}character;

//***Initialization Functions***

void character_initalization (character & user_characters);
void print_character_information (character & user_characters);

int main()
{
	showProgramHeader();
	
	character you;
	character companion;
	
	cout << "We're about to embark on a journey!" << endl;
	cout << "First, we'll need to know some information about you and your companion before we begin our adventure" << endl << endl;
	cout << "You" << "'" << "re up first!" << endl;
	character_initalization (you);
	cout << "Next, your companion!" << endl;
	character_initalization (companion);

	cout << endl << "Here" << "'" << "s the information we got for you guys" << endl;
	cout << "You-" << endl;
	print_character_information (you);
	cout << "Your companion-" << endl;
	print_character_information (companion);
}

void showProgramHeader()
{
	cout << "Miguel Villanueva \nCS 120 Lab Section 6 \nMarch 7, 2019 \nLab Assignment Number 8 \n" << endl;
}

void character_initalization (character & user_characters)
{
	cout << "Name: ";
        cin >> user_characters.character_name;
	cout << "Age: ";
	cin >> user_characters.character_age;
	cout << "Weight: ";
	cin >> user_characters.character_weight;
}

void print_character_information(character & user_characters)
{
	cout << "Name: " << user_characters.character_name << endl;
	cout << "Age: " << user_characters.character_age << endl;
	cout << "Weight: " << user_characters.character_weight << endl;
}
