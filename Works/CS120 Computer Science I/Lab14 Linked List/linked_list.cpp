void showProgramHeader();

#include <iostream>
#include <string>
using namespace std;
//***NODE CLASS***
class node
{
    public:
        string name;
        int ID;
        node *next;
        node();
};
//***LINKED LIST CLASS***
class linkedList
{
    public:
        node *head;
        linkedList();
        void print();
        string search();
};

int main()
{
    showProgramHeader();
    linkedList *llist;
    node *ptr = new node;
    ptr->next = new node;
    ptr->next = new node;
    ptr->next = new node;
}
//***PROGRAM HEADER***
void showProgramHeader()
{
    cout << "Miguel Villanueva \nCS 120 Lab Section 6 \nMay 1, 2019 \nLab Assignment Number 14\n" << endl;
}
//***NODE CONSTRUCTOR***
node::node()
{
    cout << "Enter a name(one word): ";
    cin >> name;
    cout << "Next enter an ID(three numbers): ";
    cin >> ID;
    next = NULL;
}
//***LINKED LIST CONSTRUCTOR***
linkedList::linkedList()
{
    head = NULL;
}
