void showProgramHeader();
void MegaMillions();
void PowerBall();

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void megaArray();
void powerArray();

//***GLOBAL VARIABLES***
int megaWhiteBall[70];
int megaBall;
int powerWhiteBall[69];
int powerBall;
int matchingNumbers;

int main()
{
    showProgramHeader();

    int lottery;
    cout << "Thanks for participating in the lottery!" << endl;
    cout << "Would you like to play MegaMillions(1) or PowerBall(2)" << endl;
    cin >> lottery;

    do
    {
        if (lottery == 1)
        {
            MegaMillions();
            break;
        }
        else if (lottery == 2)
        {
            PowerBall();
            break;
        }
        else
        {
            cout << "Would you like to play MegaMillions(1) or PowerBall(2)" << endl;
            cin >> lottery;
        }
    }
    while (lottery != 1 || lottery != 2);

    return 0;
}

void showProgramHeader()
{
    cout << "Miguel Villanueva \nCS 120 Section 6 \nMarch 27, 2019 \nHomework Number 8\n" << endl;
}

void megaArray()
{
    for (int i = 0; i < 70; i++)
    {
        megaWhiteBall[i] = i + 1;
    }
    //***SHUFFLE WHITE BALLS***
    srand(time(NULL));

    cout << endl << "The five MegaMillions numbers are: ";
    for (int m = 0; m < 5; m++)
    {
        int temp = megaWhiteBall[m];
        int randomIndex = rand() % 70;
        megaWhiteBall[m] = megaWhiteBall[randomIndex];
        megaWhiteBall[randomIndex] = temp;
        cout << megaWhiteBall[m] << " ";
    }
    //***RANDOM MEGABALL NUMBER***
    megaBall = rand() % 25;
    cout << endl << "And the MegaBall number is: " << megaBall << endl;
}

void powerArray()
{
    for (int i = 0; i < 69; i++)
    {
        powerWhiteBall[i] = i + 1;
    }
    //***SHUFFLE WHITE BALLS***
    srand(time(NULL));

    cout << endl << "The five PowerBall numbers are: ";
    for (int m = 0; m < 5; m++)
    {
        int temp = powerWhiteBall[m];
        int randomIndex = rand() % 69;
        powerWhiteBall[m] = powerWhiteBall[randomIndex];
        powerWhiteBall[randomIndex] = temp;
        cout << powerWhiteBall[m] << " ";
    }
    //***RANDOM POWERBALL NUMBER***
    powerBall = rand() % 26;
    cout << endl << "The main PowerBall number is: " << powerBall << endl;
}

void MegaMillions()
{
    int userNumber[5];
    int userMegaBall;
    cout << endl << "You chose MegaMillions!" << endl;
    cout << "Enter five numbers between 1-70" << endl;
    for (int i = 0; i < 5; i++)
    {
        cin >> userNumber[i];
    }
    cout << "Now, choose a MegaBall number between 1-25" << endl;
    cin >> userMegaBall;

    megaArray();
    //***MATCHING NUMBERS***
    for (int k = 0; k < 5; k++)
    {
        if (megaWhiteBall[k] == userNumber[k])
        {
            matchingNumbers = matchingNumbers + 1;
        }
    }
    if (userMegaBall == megaBall)
    {
        matchingNumbers = matchingNumbers + 1;
    }

    //***RESULT***
    if (matchingNumbers == 6)
    {
        cout << endl << "You won the MegaMillions lottery! Too bad it isn't real!" << endl;
    }
    else
    {
        cout << endl << "You lost the MegaMillions lottery..." << endl;
        cout << "However, at least it isn't real!" << endl;
    }
}

void PowerBall()
{
    int userNumber[5];
    int userPowerBall;
    cout << endl << "You chose PowerBall!" << endl;
    cout << "Enter five numbers between 1-69" << endl;
    for (int i = 0; i < 5; i++)
    {
        cin >> userNumber[i];
    }
    cout << "Now, choose a PowerBall number between 1-26" << endl;
    cin >> userPowerBall;

    powerArray();
    //***MATCHING NUMBERS***
    for (int k = 0; k < 5; k++)
    {
        if (powerWhiteBall[k] == userNumber[k])
        {
            matchingNumbers = matchingNumbers + 1;
        }
    }
    if (userPowerBall == powerBall)
    {
        matchingNumbers = matchingNumbers + 1;
    }

    //***RESULT***
    if (matchingNumbers == 6)
    {
        cout << endl << "You won the PowerBall lottery! Too bad it isn't real!" << endl;
    }
    else
    {
        cout << endl << "You lost the PowerBall lottery..." << endl;
        cout << "However, at least it isn't real!" << endl;
    }
}
