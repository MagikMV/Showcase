/* hw2.cpp
 *
 * Miguel Villanueva
 * CS 336
 * September 7, 2021
 */

#include <iostream>
#include <algorithm>  // For transform()
#include <string>
using namespace std;

void Encrypt();
void DecryptWithKey();
void DecryptWithout();

int main()
{
    int choice;

    while(1)
    {
	cout << "========================================================" << endl;
	cout << "    0 to exit" << endl;
	cout << "    1 to do CAESAR Cipher Encryption" << endl;
	cout << "    2 to do CAESAR Cipher Decryption with a given key" << endl;
	cout << "    3 to do CAESAR Cipher Decryption with an unknown key" << endl;
	cout << "What would you like to do?" << endl << "    ";

	cin >> choice; // Note, I did not add a check for correct inputs

	if(choice == 0)
	    break;
	else if(choice == 1)
	    Encrypt();
	else if(choice == 2)
	    DecryptWithKey();
	else if(choice == 3)
	    DecryptWithout();
	else
	   cout << "> Please enter 0, 1, 2, or 3" << endl << endl;
    }
    cout << "> Program exited..." << endl;

    return 0;
}

void Encrypt()
{
    string plainText;
    int textLength, key;

    cout << "Enter the plaintext" << endl << "    ";
    cin.ignore();
    getline(cin, plainText); // Again no check for correct input
    textLength = plainText.length();
    transform(plainText.begin(), plainText.end(), plainText.begin(), ::toupper);

    cout << "Enter the key" << endl << "    ";
    cin >> key;

    for(int i = 0; i < textLength; i++)
    {
	for(int j = 0; j < key; j++)
	{
	    if(plainText[i] == ' ')
		continue;

	    if(plainText[i] == 'Z')
		plainText[i] = 'A';
	    else
		plainText[i]++;
	}
    }
    cout << "> Ciphertext: " << plainText << endl << endl;
}


void DecryptWithKey()
{
    string cipherText;
    int textLength, key;

    cout << "Enter the ciphertext" << endl << "    ";
    cin.ignore();
    getline(cin, cipherText); // No check for correct input
    textLength = cipherText.length();
    transform(cipherText.begin(), cipherText.end(), cipherText.begin(), ::toupper);

    cout << "Enter the key" << endl << "    ";
    cin >> key;

    for(int i = 0; i < textLength; i++)
    {
	for(int j = 0; j < key; j++)
	{
	    if(cipherText[i] == ' ')
                continue;

	    if(cipherText[i] == 'A')
		cipherText[i] = 'Z';
	    else
		cipherText[i]--;
	}
    }
    cout << "> Plaintext: " << cipherText << endl << endl;
}

void DecryptWithout()
{
    string cipherText;
    int textLength;

    cout << "Enter the ciphertext" << endl << "    ";
    cin.ignore();
    getline(cin, cipherText); // No check for correct input
    textLength = cipherText.length();
    transform(cipherText.begin(), cipherText.end(), cipherText.begin(), ::toupper);

    for(int i = 0; i < 26; i++)
    {
	for(int j = 0; j < textLength; j++)
	{
	    if(cipherText[j] == ' ')
                continue;

	    if(cipherText[j] == 'A')
                cipherText[j] = 'Z';
            else
                cipherText[j]--;
	}

	cout << ">Plaintext with key " << i + 1 << ": " << cipherText << endl << endl;
    }
}
