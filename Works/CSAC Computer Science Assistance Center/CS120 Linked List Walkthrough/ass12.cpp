/* ass12.cpp
 *
 * Miguel Villanueva
 * CS 120 [CSAC]
 * November 18, 2021
 */

#include<iostream>
#include<string>
using namespace std;

class node
{
    private:
	    node *next;
	    string name;
    public:
     	void setnext(node *n){next = n;}  // inline function
     	void setdata(string n){name = n;} // inline function
     	void print(); // defined below
	    int length();
	    void append(node *p);
	    void clear();
	    void removeFromEnd();
};

void node::print()
{
    cout << name << endl;
    if(next != NULL)
      next->print();
}

int node::length()
{
    if(this == NULL)
	    return 0;

    if(next != NULL)
	    return 1 + next->length();
    else
	    return 1;
}

void node::append(node *p)
{
    if(next != NULL)
	    next->append(p);
    else
	    next = p;
}

void node::clear()
{
    if(next != NULL)
    {	
	    next->clear();
    }
    delete next;
        next = NULL;
}

void node::getOuttaHeee()
{
    node *head = this;
    //cout << "Stinky " << head->name << endl;

    head->removeFromEnd();
    head->removeFromEnd();
    head->removeFromEnd();
    head->removeFromEnd();
    //delete head;
    //head = NULL;
    //head->removeFromEnd();
    //head = NULL;
}

void node::removeFromEnd()
{
    node *curr = this;
    node *prev = curr;

    /*if(curr->next == NULL)
    {
	cout << "Does this code execute" << endl;
	delete curr;
	curr = NULL;
	return;
    }*/

    while(curr->next != NULL)
    {
        prev = curr;
        curr = curr->next;
    }
    delete curr;
    prev->next = NULL;
}

int main(){
    node *head, *temp;      // pointers to a node object
    temp = new node();      // create a new node object
    temp->setdata("Sally"); // add data
    temp->setnext(NULL);    // make the next object Null
    head = temp;            // make head point to the beginning of the list
    temp = new node();      // create another new node object
    temp->setdata("Fred");  // add data
    temp->setnext(head);    // 'point' the new object to the beginning of the list
    head = temp;            // make head point to the new beginning of the list
    temp = new node();      // repeat
    temp->setdata("Anne");
    temp->setnext(head);
    head = temp;
    head->print();          // print the list

    temp = new node();
    temp->setdata("Jeff");
    temp->setnext(NULL);
    head->append(temp);
    
    temp = new node();
    temp->setdata("Jeff2");
    temp->setnext(NULL);
    head->append(temp);
    
    cout << endl;
    head->print();

    cout << endl << "List length: " << head->length() << endl;
    //head->removeFromEnd();
    head->getOuttaHeee();
    //head->clear();
    //delete head;
    //head = NULL;   
    cout << endl << "List length: " << head->length() << endl;
    //head->print();  // Don't call when list is empty
}
