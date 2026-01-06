/* queue.h
 *
 * Definition of queue class
 */

#ifndef QUEUEL_H_INCLUDED
#define QUEUEL_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

struct node
{
    int enterTime;
    string name;
    int items;

    // how long a customer has been in checkout
    int timeInCheckout;

    node *next;
};

class Queue
{
    private:
        node *head;
        node *tail;

        int Count;
    public:
        Queue();
        void Enqueue(node *a);
        node* Dequeue();
        void displayQueue();
        bool isEmpty();
        node* removeEnd();
        node* getFront();
        node* getEnd();

        // returns number of nodes in queue
        int getSize()
        {
            return Count;
        }
};

#endif // QUEUEL_H_INCLUDED
