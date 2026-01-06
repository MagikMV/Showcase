/* stack.cpp
 *
 * Definition of Stack class member functions
 */

 #include <iostream>
 #include "stack.h"

 using namespace std;

//***STACK CONSTRUCTOR***
Stack::Stack()
{
    head = NULL;
}
//***PUSH MEMBER FUNCTION FOR STACK***
void Stack::push(int neighborPosition)
{
    node *temp = new node;
    temp->position = neighborPosition;
    if(head == NULL)
    {
        head = temp;
        temp->next = NULL;
    }
    else
    {
        temp->next = head;
        head = temp;
    }
}
//***POP MEMBER FUNCTION FOR STACK***
int Stack::pop()
{   if(head == NULL)
    {
        return -1;
    }
    else
    {
        node *temp = head;
        head = head->next;
        temp->next = NULL;
        return temp->position;
    }
}
//***PRINT MEMBER FUNCTION FOR STACK***
void Stack::printStack()
{
    node *temp = head;
    while(temp != NULL)
    {
        cout << temp->position << " ";
        temp = temp->next;
    }
}
//***IS EMPTY MEMBER FUNCTION***
bool Stack::isEmpty()
{
    if(head == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }

}
//***ALREADY IN STACK MEMBER FUNCTION***
bool Stack::alreadyInStack(int *&Array, int arraySize)
{
    node *temp = head;
    while(temp->next != NULL)
    {
        for(int i = 0; i < arraySize; i++)
        {
            if(temp->position == Array[i])
            {
                return true;
            }
        }
        temp = temp->next;
    }
    return false;
}
