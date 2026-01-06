/* stack.h
 *
 * Definition of Stack class
 */

#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <iostream>

using namespace std;

struct node
{
    int position; // Position in 1-D array
    node *next;
};

class Stack
{
    private:
        node *head;
    public:
        Stack();
        void push(int position);
        int pop();
        void printStack();
        bool isEmpty();
        bool alreadyInStack(int *&Array, int arraySize);
};

#endif // STACK_H_INCLUDED
