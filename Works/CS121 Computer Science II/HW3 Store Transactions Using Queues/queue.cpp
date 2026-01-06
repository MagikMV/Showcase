/* queue.cpp
 *
 * Definition of queue class member functions
 */

#include <iostream>
#include <iomanip>

#include "queue.h"

using namespace std;

// constructor
Queue::Queue()
{
    head = NULL;
    tail = head;

    Count = 0;
}

// add node to end of queue
void Queue::Enqueue(node *a)
{
    // allocate
    node *p = new node;

    // initialize
    p->enterTime = a->enterTime;
    p->name = a->name;
    p->items = a-> items;
    p->timeInCheckout = 0;
    p->next = NULL;
    Count++;

    // empty case
    if(head == NULL)
    {
        head = p;
        tail = head;
        p->next = NULL;
    }
    // add node
    else
    {
        node *temp = head;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = p;
        tail = p;
    }
}

// remove node from front of queue
    // and return node pointer
node* Queue::Dequeue()
{
    node *a = head;

    // empty case
    if(a == NULL)
    {
        // empty list
    }
    // remove node
    else
    {
        // change head location
        head = head->next;
        a->next = NULL;

        Count--;
    }
    return a;
}

// print desired queue
void Queue::displayQueue()
{
    node *temp = head;
    if(temp == NULL)
    {
        cout << "This line is empty!" << endl;
        cout << endl;
    }
    else
    {
        while(temp != NULL)
        {
            // print
            cout << left << setw(2) << temp->enterTime
            << setw(8) << temp->name << right
            << setw(2) << temp->items << endl;

            temp = temp->next;
        }
        cout << endl;
    }
}

// checks if queue is empty
bool Queue::isEmpty()
{
    node *b = head;

    if(b == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// remove node from end of queue
node* Queue::removeEnd()
{
    node *curr = head;
    node *prev = head;
    if(curr == NULL) // new  // REMOVE COMMENT
    {
        // empty case
    }
    else // new // REMOVE COMMENT
    {
        while(curr->next != NULL)
        {
            prev = curr;
            curr = curr->next;
        }
        prev->next = NULL;
        tail = prev;

        Count--;
    }
    return curr;
}

// return the head node
node* Queue::getFront()
{
    node *p = head;
    return p;
}

// return the tail node
node* Queue::getEnd()
{
    node *p = tail;
    return p;
}
