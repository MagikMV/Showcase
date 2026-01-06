/* queue.cpp
 *
 * Miguel Villanueva
 * October 28, 2021
 */

#include "queue.h"


Queue::Queue()
{
    head = NULL;
}

void Queue::enqueue(Customer c)
{
    node *temp = new node;
    temp->customer = c;
    temp->next = NULL;
    
    if(head == NULL)
	    head = temp;
    else
    {
	    node *curr = head;
	
	    while(curr->next != NULL)
	        curr = curr->next;

	    curr->next = temp;
    }
}

void Queue::leave()
{
    node *temp = new node;
    
    if(head == NULL)
	    cout << "Cannot remove from an empty queue" << endl;
    else
    {
	    temp = head;
	    head = head->next;

	    delete temp;
    }
}

bool Queue::isEmpty()
{
    if(head == NULL)
	    return true;

    return false;
}

void Queue::print()
{
    node *temp = head;

    while(temp != NULL)
    {
	    cout << temp->customer.name << endl;
	    temp = temp->next;
    } 
}
