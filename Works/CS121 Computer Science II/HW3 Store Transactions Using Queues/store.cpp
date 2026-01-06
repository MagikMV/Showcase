/* store.cpp
 *
 * CS 121 Bolden
 * Miguel Villanueva  //  vill9577@vandals.uidaho.edu
 * October 30, 2019
 *
 * Eluktronics P65_67HSHP  //  Intel Core i7-7700HQ
 * GCC 5.1.0
 *
 * Program Description:
 *      Store transactions
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "queue.cpp"

using namespace std;

// prototypes
node* readData(ifstream &infile, Queue preCheckout);
void eItemRemove(Queue expressLine);
void rItemRemove(Queue regularLine);
void decreaseItemCount(Queue express, Queue line1, Queue line2);
bool transactionComplete(Queue checkoutLine);
node* changeLines(Queue express, Queue line1, Queue line2);
node* enterCheckout(Queue preCheckout, int &time);
void displayStore(Queue preCheckout, Queue express,
                  Queue line1, Queue line2);

int main()
{
    int time = 0;
    Queue preCheckout;
    ifstream infile;
    node *p = readData(infile, preCheckout);
    Queue shopping;

    // save data file
    while(p != NULL)
    {
        shopping.Enqueue(p);
        p = p->next;
    }
    shopping.displayQueue();


    // "r" for regular line: 4 clock cycles
    Queue rLine1;
    Queue rLine2;

    // "e" for express line: 2 clock cycles
    Queue eLine3;

    // print store before transactions
    displayStore(shopping, eLine3, rLine1, rLine2);

    // testing to show that code works in some sense
    cout << endl << "/////TESTING//////" << endl;
        // allocation, simulating data read
    node *temp = new node;
    temp->enterTime = 1;
    temp->name = "Miguel";
    temp->items = 1;
    node *temp1 = new node;
    temp1->enterTime = 2;
    temp1->name = "Bob";
    temp1->items = 5;
    node *temp2 = new node;
    temp2->enterTime = 3;
    temp2->name = "John";
    temp2->items = 4;

        // enter checkout simulation
    rLine2.Enqueue(temp);
    cout << endl << "Regular line 2 checkout:" << endl;
    rLine2.displayQueue();
        // decrease item simulation
    decreaseItemCount(eLine3, rLine1, rLine2);
    cout << endl << "Regular line 2 checkout:" << endl;
    rLine2.displayQueue();
    rLine2.getFront()->timeInCheckout = 4;
    decreaseItemCount(eLine3, rLine1, rLine2);
    cout << endl << "Regular line 2 checkout:" << endl;
    rLine2.displayQueue();

    // one of three examples for leaving checkout
        // this has to happen in order to account for this instance
    if(transactionComplete(rLine2) == true)
    {
        delete rLine2.Dequeue();
    }


    rLine2.Enqueue(temp1);
    rLine2.Enqueue(temp);
    cout << endl << "Regular line 2 checkout:" << endl;
    rLine2.displayQueue();
    rLine1.Enqueue(temp);
    rLine1.Enqueue(temp1);
    cout << endl << "Regular line 1 checkout:" << endl;
    rLine1.displayQueue();

    // example of the 12 conditions for changing lines
    if(rLine2.getFront()->next != NULL && rLine2.getEnd()->items <= 10)
    {
         //delete changeLines(eLine3, rLine1, rLine2);
         eLine3.Enqueue(changeLines(eLine3, rLine1, rLine2));
    }
    cout << endl << "Changing of lines" << endl << endl;
    cout << endl << "Regular line 2 checkout:" << endl;
    rLine1.displayQueue();
    cout << "Regular line 2 checkout:" << endl;
    rLine2.displayQueue();
    cout << "Express line checkout:" << endl;
    eLine3.displayQueue();

    do
    {
        // decrease items
        decreaseItemCount(eLine3, rLine1, rLine2);

        // leave checkout
        if(transactionComplete(eLine3) == true)
        {
            delete eLine3.Dequeue();
        }
        if(transactionComplete(rLine2) == true)
        {
            delete rLine2.Dequeue();
        }
        if(transactionComplete(rLine1) == true)
        {
            delete rLine1.Dequeue();
        }

        // change checkout lines
                // express checkout conditions
                        // regular line 2 eligibility
        if(rLine2.getFront()->next != NULL && rLine2.getEnd()->items > 10)
        {
            delete changeLines(eLine3, rLine1, rLine2);
        }
        if(rLine2.getFront()->next != NULL && rLine2.getEnd()->items <= 10)
        {
            eLine3.Enqueue(changeLines(eLine3, rLine1, rLine2));
        }
                        // regular line 1 eligibility
        if(rLine1.getFront()->next != NULL && rLine1.getEnd()->items > 10)
        {
            delete changeLines(eLine3, rLine1, rLine2);
        }
        if(rLine1.getFront()->next != NULL && rLine1.getEnd()->items <= 10)
        {
            eLine3.Enqueue(changeLines(eLine3, rLine1, rLine2));
        }
                // regular line 1 conditions
                        // express line eligibility
        if(eLine3.getFront()->next == NULL)
        {
            delete changeLines(eLine3, rLine1, rLine2);
        }
        if(eLine3.getFront()->next != NULL)
        {
            rLine1.Enqueue(changeLines(eLine3, rLine1, rLine2));
        }
                        // regular line 2 eligibility
        if(rLine2.getFront()->next == NULL)
        {
            delete changeLines(eLine3, rLine1, rLine2);
        }
        if(rLine2.getFront()->next != NULL)
        {
            rLine1.Enqueue(changeLines(eLine3, rLine1, rLine2));
        }
                // regular line 2 conditions
                        // express line eligibility
        if(eLine3.getFront()->next == NULL)
        {
            delete changeLines(eLine3, rLine1, rLine2);
        }
        if(eLine3.getFront()->next != NULL)
        {
            rLine2.Enqueue(changeLines(eLine3, rLine1, rLine2));
        }
                        // regular line 1 eligibility
        if(rLine1.getFront()->next == NULL)
        {
            delete changeLines(eLine3, rLine1, rLine2);
        }
        if(rLine1.getFront()->next != NULL)
        {
            rLine2.Enqueue(changeLines(eLine3, rLine1, rLine2));
        }

        // enter checkout
        if(shopping.getFront()->enterTime == time)
        {
                // express line is shortest
            if(eLine3.getSize() < rLine1.getSize()
               && eLine3.getSize() < rLine2.getSize())
            {
                if(shopping.getFront()->items > 10)
                {
                    rLine1.Enqueue(shopping.Dequeue());
                }
                else if(shopping.getFront()->items <= 10)
                {
                    eLine3.Enqueue(shopping.Dequeue());
                }
            }
                // regular line 1 is shortest
            else if(rLine1.getSize() < eLine3.getSize()
                    && rLine1.getSize() < rLine2.getSize())
            {
                rLine1.Enqueue(shopping.Dequeue());
            }
                // regular line 2 is shortest
            else if(rLine2.getSize() < eLine3.getSize()
                    && rLine2.getSize() < rLine1.getSize())
            {
                rLine2.Enqueue(shopping.Dequeue());
            }
                // express and line 1 are shortest
            else if(eLine3.getSize() == rLine1.getSize()
                    && eLine3.getSize() < rLine2.getSize()
                    && rLine1.getSize() < rLine2.getSize())
            {
                if(shopping.getFront()->items > 10)
                {
                    rLine1.Enqueue(shopping.Dequeue());
                }
                else if(shopping.getFront()->items <= 10)
                {
                    eLine3.Enqueue(shopping.Dequeue());
                }
            }
                // express and line 2 are shortest
            else if(eLine3.getSize() == rLine2.getSize()
                    && eLine3.getSize() < rLine1.getSize()
                    && rLine2.getSize() < rLine1.getSize())
            {
                if(shopping.getFront()->items > 10)
                {
                    rLine2.Enqueue(shopping.Dequeue());
                }
                else if(shopping.getFront()->items <= 10)
                {
                    eLine3.Enqueue(shopping.Dequeue());
                }
            }
                // line 1 and line 2 are shortest
            else if(rLine1.getSize() == rLine2.getSize()
                    && rLine1.getSize() < eLine3.getSize()
                    && rLine2.getSize() < eLine3.getSize())
            {
                rLine1.Enqueue(shopping.Dequeue());
            }
                // all lines are shortest
            else if(eLine3.getSize() == rLine1.getSize()
                    && rLine1.getSize() == rLine2.getSize()
                    && rLine2.getSize() == eLine3.getSize())
            {
                if(shopping.getFront()->items > 10)
                {
                    rLine1.Enqueue(shopping.Dequeue());
                }
                else if(shopping.getFront()->items <= 10)
                {
                    eLine3.Enqueue(shopping.Dequeue());
                }
            }
        }
        ++time;
    }while(time < 1 && rLine1.isEmpty() == true
           && rLine2.isEmpty() == true && eLine3.isEmpty() == true);

    // print store after transactions
    displayStore(shopping, eLine3, rLine1, rLine2);
}

// read data file into a queue
node* readData(ifstream &infile, Queue preCheckout)
{
    string fileName;

    // file input
    cout << "Enter a data file name you wish to read (include extension): ";
    getline(cin, fileName);

    // open stream
    infile.open(fileName.c_str(), ios::in);

    // error
    if(!infile)
    {
        cout << "Unable to open input file \"" << fileName << "\"" << endl;
        exit(1);
    }
    // store
    int enterTime;
    string name;
    int items;
    while(infile >> enterTime >> name >> items)
    {
        node *temp = new node;
        temp->enterTime = enterTime;
        temp->name = name;
        temp->items = items;
        preCheckout.Enqueue(temp);
    }
    infile.close();
    return preCheckout.getFront();
}

// remove an item from an express line customer
void eItemRemove(Queue expressLine)
{
    if(expressLine.isEmpty() == true)
    {
        // do nothing
    }
    else
    {
        if(expressLine.getFront()->timeInCheckout % 2 == 0
           && expressLine.getFront()->timeInCheckout > 0)
        {
            expressLine.getFront()->items -= 1;
        }
    }
}

// remove an item from a regular line customer
void rItemRemove(Queue regularLine)
{
    if(regularLine.isEmpty() == true)
    {
        // do nothing
    }
    else
    {
        if(regularLine.getFront()->timeInCheckout % 4 == 0
           && regularLine.getFront()->timeInCheckout > 0)
        {
            regularLine.getFront()->items -=1;
        }
    }
}

// item count is decreased based on clock cycle
    // applied to head customer of a each checkout line
void decreaseItemCount(Queue express, Queue line1, Queue line2)
{
    eItemRemove(express);
    rItemRemove(line1);
    rItemRemove(line2);
}

// checks if head customer is ready to leave
    // dequeues individual when items are equal to zero
    // deallocates memory of head customer
bool transactionComplete(Queue checkoutLine)
{
    if(checkoutLine.isEmpty() == true)
    {
        // do nothing
        return false;
    }
    else
    {
        if(checkoutLine.getFront()->items == 0)
        {
            cout << checkoutLine.getFront()->name << " has left the checkout!";
            cout << endl;
            delete checkoutLine.Dequeue();
            checkoutLine.displayQueue();
        }
        return true;
    }
}

node* changeLines(Queue express, Queue line1, Queue line2)
{
    // default return value
    node *a = new node;

    // if the express checkout line is empty
    if(express.isEmpty() == true)
    {
            // therefore line2 is conditioned
            if(line2.getFront()->next == NULL)
            {
                // do nothing
            }
            else if(line2.getFront()->next != NULL)
            {
                // express line conditions
                if(line2.getEnd()->items > 10)
                {
                    // do nothing
                }
                else if(line2.getEnd()->items <= 10)
                {
                    return line2.removeEnd();
                }
            }
            // therefore line1 is conditioned
            if(line1.getFront()->next == NULL)
            {
                // do nothing
            }
            else if(line1.getFront()->next != NULL)
            {
                // express line conditions
                if(line2.getEnd()->items > 10)
                {
                    // do nothing
                }
                else if(line2.getEnd()->items <=10)
                {
                    return line1.removeEnd();
                }
            }
    }

    // if checkout line1 is empty
    if(line1.isEmpty() == true)
    {
            // therefore line2 is conditioned
            if(line2.getFront()->next == NULL)
            {
                // do nothing
            }
            else if(line2.getFront()->next != NULL)
            {
                return line2.removeEnd();
            }
            // therefore express line is conditioned
            if(express.getFront()->next == NULL)
            {
                // do nothing
            }
            else if(line2.getFront()->next != NULL)
            {
                return express.removeEnd();
            }
    }

    // if checkout line2 is empty
    if(line2.isEmpty() == true)
    {
        // therefore line1 is conditioned
        if(line1.getFront()->next == NULL)
        {
            // do nothing
        }
        else if(line1.getFront()->next != NULL)
        {
            return line1.removeEnd();
        }

        // therefore express line is conditioned
        if(express.getFront()->next == NULL)
        {
            // do nothing
        }
        else if(express.getFront()->next != NULL)
        {
            return express.removeEnd();
        }
    }
    return a;
}

node* enterCheckout(Queue preCheckout, int &time)
{
    node *a = new node;
    if(preCheckout.isEmpty() == true)
    {
        // do nothing
    }
    else if(preCheckout.isEmpty() == false)
    {
        if(preCheckout.getFront()->enterTime == time)
        {
            return preCheckout.Dequeue();
        }
        else if(preCheckout.getFront()->enterTime == time)
        {
            // do nothing
        }
    }
    return a;
}

void displayStore(Queue preCheckout, Queue express,
                  Queue line1, Queue line2)
{
    cout << endl << "Customers who are still shopping:" << endl;
    preCheckout.displayQueue();
    cout << "Express line checkout:" << endl;
    express.displayQueue();
    cout << "Regular line 1 checkout:" << endl;
    line1.displayQueue();
    cout << "Regular line 2 checkout:" << endl;
    line2.displayQueue();
}
