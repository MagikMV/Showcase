/* queue.h
 *
 * Miguel Villanueva
 * October 28, 2021
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>
using namespace std;

struct Customer
{
    int entryTime;
    string name;
    char activity;
    int transactions;
};

struct node
{
    Customer customer;
    node *next;
};

class Queue
{
    private:
	    node *head;
    public:
	    Queue();
	    void enqueue(Customer c);
	    void leave();
	    bool isEmpty();
	    void print();
};

#endif // QUEUE_H
