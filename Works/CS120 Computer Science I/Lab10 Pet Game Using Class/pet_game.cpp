void showProgramHeader();

#include <iostream>
#include <string>

using namespace std;
//***PET CLASS***
class pet{
    private:
        int hunger;
        int happy;
        string name;
        string species;
    public:
        pet();
        void play();
        void feed();
        void sleep();
        void print();
        int check_health();
};

int main()
{
    showProgramHeader();

    pet pet1;
    int choice;
    int health_check;
    do
    {
        pet1.print();
        cout << "What would you like to do with your pet?" << endl;
        cout << " Play  (1) \n Feed  (2) \n Sleep (3) \n Exit  (0) \n";
        cin >> choice;
        switch(choice)
        {
            case 1:
                pet1.play();
                break;
            case 2:
                pet1.feed();
                break;
            case 3:
                pet1.sleep();
                break;
        }
        health_check = pet1.check_health();
    }while(choice != 0 && health_check != 1);
    cin.ignore();
    cout << "Press enter to exit." << endl;
    cin.ignore();
    return 0;
}

void showProgramHeader()
{
    cout << "Miguel Villanueva \nCS 120 Lab Section 6 \nMarch 28, 2019 \nLab Assignment Number 10 \n" << endl;
}
//***CONSTRUCTOR CREATES PET W/ NEW STARTING VALUES***
pet::pet()
{
    hunger = 50;
    happy = 50;
    cout << "Pet's name? (One word) " << endl;
    cin >> name;
    cout << "What species is your pet? (One word) " << endl;
    cin >> species;
}
//***MEMBER FUNCTION FOR PLAYING WITH PET***
void pet::play()
{
    int choice = 0;
    cout << "What should we play?" << endl;
    cout << " Fetch (1) \n Roll over (2) \n";
    cin >> choice;
    switch(choice)
    {
        case(1):
            cout << "\nFetching is SO FUN!" << endl;
            happy += 10;
            hunger += 5;
            break;
        case(2):
            cout << "\nWowzers, rolling over is fun!" << endl;
            happy += 5;
            hunger += 1;
            break;
        default:
            cout << "Not a valid choice." << endl;

    }
}
//***MEMBER FUNCTION FOR FEEDING PET***
void pet::feed()
{
    int choice = 0;
    cout << "What do you want to feed your pet?" << endl;
    cout << " Treat (1) \n Bite (2) \n";
    cin >> choice;
    switch(choice)
    {
        case(1):
            cout << "\nMMM, treats are yummy!" << endl;
            happy += 1;
            hunger -= 3;
            break;
        case(2):
            cout << "\nMMM, What a delicious bite!" << endl;
            hunger -= 5;
            break;
        default:
            cout << "Not a valid choice." << endl;
    }
}
//***MEMBER FUNCTION FOR PET TO SLEEP***
void pet::sleep()
{
    cout << "\nZZZ, sleep is great!" << endl;
    happy += 15;
    hunger +=10;
}
//***MEMBER FUNCTION FOR PRINTING PET INFORMATION***
void pet::print()
{
    cout << "\nYour pet " << species << ": " << name << " is " << endl;
    cout << "Happy: " << happy << endl;
    cout << "Hungry: " << hunger << endl;
}
//***MEMBER FUNCTION FOR CHECKING PET HEALTH***
int pet::check_health()
{
    if(hunger >= 100)
    {
        cout << "\nYour pet has starved." << endl;
        return 1;
    }
    if(happy <= 0)
    {
        cout << "\nYour pet has died of a broken heart." << endl;
        return 1;
    }
    return 0;
}
