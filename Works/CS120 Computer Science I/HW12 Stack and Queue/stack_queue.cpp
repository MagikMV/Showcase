void showProgramHeader();

#include <iostream>
using namespace std;
//***NODE STRUCT***
struct node
{
    char letter; // For stack
    int number; // For queue
    node *next;
};
//***CLASS LINKED LIST FOR STACK***
class stackLinkedList
{
    private:
        node *head; //, *tail; // Bad code
    public:
        stackLinkedList();
        //void createStackNode(char value); // Bad code
        void printStack();
        void push(char value);
        char pop();
        bool emptyStack();
};
//***CLASS LINNKED LIST FOR QUEUE***
class queueLinkedList
{
    private:
        node *head; //, *tail; // Bad code
    public:
        queueLinkedList();
        //void createQueueNode(int value); // Bad code
        void printQueue();
        void insert(int value);
        int remove();
        bool emptyQueue();
};
//***MAIN FUNCTION***
int main()
{
    showProgramHeader();
    // Exercise 12.1 - Stack
    cout << "****************** EXERCISE 12.1 *********************" << endl;
    stackLinkedList stack;
    //cout << "Initial stack:" << endl; // Bad code
    //stack.createStackNode('a'); // Bad code
    //stack.createStackNode('b'); // Bad code
    //stack.createStackNode('c'); // Bad code
    //stack.printStack(); // Bad code
    cout << "Pushing the characters {t,e,s,t,a,n,g} onto the stack:" << endl;
    stack.push('t');
    stack.push('e');
    stack.push('s');
    stack.push('t');
    stack.push('a');
    stack.push('n');
    stack.push('g');
    stack.printStack();
    cout << "Popping three characters off the stack:" << endl;
    stack.pop();
    stack.pop();
    stack.pop();
    stack.printStack();
    cout << "Pushing the characters {i,n,g} onto the stack:" << endl;
    stack.push('i');
    stack.push('n');
    stack.push('g');
    stack.printStack();
    cout << "Popping the remaining characters off the stack and printing them in order of popping:" << endl;
    while(stack.emptyStack() != true)
    {
        cout << stack.pop() << " ";
    }
    cout << endl << endl;
    // Exercise 12.2 - Queue
    cout << "****************** EXERCISE 12.2 *********************" << endl;
    queueLinkedList queue;
    //cout << "Initial queue:" << endl; // Bad code
    //queue.createQueueNode(7); // Bad code
    //queue.createQueueNode(8); // Bad code
    //queue.createQueueNode(9); // Bad code
    //queue.printQueue();
    cout << "Inserting the integers {1,2,3,4,7,8} into the queue:" << endl;
    queue.insert(1);
    queue.insert(2);
    queue.insert(3);
    queue.insert(4);
    queue.insert(7);
    queue.insert(8);
    queue.printQueue();
    cout << "Removing two integers from the queue:" << endl;
    queue.remove();
    queue.remove();
    queue.printQueue();
    cout << "Inserting the integers {5,6} into the queue:" << endl;
    queue.insert(5);
    queue.insert(6);
    queue.printQueue();
    cout << "Removing the remaining integers from the queue and printing them in order of removal:" << endl;
    while(queue.emptyQueue() != true)
    {
        cout << queue.remove() << " ";
    }
    cout << endl;
}
//***PROGRAM HEADER***
void showProgramHeader()
{
    cout << "Miguel Villanueva \nCS 120 Section 6 \nMay 2, 2019 \nHomework Number 12\n" << endl;
}
//***STACK LINKED LIST CONSTRUCTOR***
stackLinkedList::stackLinkedList()
{
    head = NULL;
}
//***QUEUE LINKED LIST CONSTRUCTOR***
queueLinkedList::queueLinkedList()
{
    head = NULL;
}
//*********************** BAD CODE *******************************
//***CREATE NODE MEMBER FUNCTION FOR STACK***
//void stackLinkedList::createStackNode(char value)
//{
    //node *temp = new node;
    //temp->letter = value;
    //temp->next = NULL;
    //if(head == NULL)
    //{
        //head = temp;
        //tail = temp;
        //temp = NULL;
    //}
    //else
    //{
        //tail->next = temp;
        //tail = temp;
    //}
//}
//*********************** BAD CODE *******************************
//***CREATE NODE MEMBER FUNCTION FOR QUEUE***
//void queueLinkedList::createQueueNode(int value)
//{
    //node *temp = new node;
    //temp->number = value;
    //temp->next = NULL;
    //if(head == NULL)
    //{
        //head = temp;
        //tail = temp;
        //temp = NULL;
    //}
    //else
    //{
        //tail->next = temp;
        //tail = temp;
    //}
//}
//***PRINT MEMBER FUNCTION FOR STACK***
void stackLinkedList::printStack()
{
    node *temp = new node;
    temp = head;
    while(temp != NULL)
    {
        cout << temp->letter << " ";
        temp = temp->next;
    }
    cout << endl << endl;
}
//***PRINT MEMBER FUNCTION FOR QUEUE***
void queueLinkedList::printQueue()
{
    node *temp = new node;
    temp = head;
    while(temp != NULL)
    {
        cout << temp->number << " ";
        temp = temp->next;
    }
    cout << endl << endl;
}
//***PUSH MEMBER FUNCTION FOR STACK***
void stackLinkedList::push(char value)
{
    node *temp = new node;
    temp->next = NULL;
    temp->letter = value;
    temp->next = head;
    head = temp;
}
//***INSERT MEMBER FUNCTION FOR QUEUE***
void queueLinkedList::insert(int value)
{
    node *ptr = new node;
    ptr->next = NULL;
    ptr->number = value;
    node *temp = head;
    if(head == NULL)
    {
        head = ptr;
    }
    else
    {
        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = ptr;
    }
}
//***POP MEMBER FUNCTION FOR STACK***
char stackLinkedList::pop()
{
    node *temp = new node;
    temp = head;
    head = head->next;
    return temp->letter;
}
//***REMOVE MEMBER FUNCTION FOR QUEUE***
int queueLinkedList::remove()
{
    node *temp = new node;
    temp = head;
    head = head->next;
    return temp->number;
}
//***EMPTY MEMBER FUNCTION FOR STACK***
bool stackLinkedList::emptyStack()
{
    if(head == NULL)
        return true;
    else
        return false;
}
//***EMPTY MEMBER FUNCTION FOR QUEUE***
bool queueLinkedList::emptyQueue()
{
     if(head == NULL)
        return true;
    else
        return false;
}
