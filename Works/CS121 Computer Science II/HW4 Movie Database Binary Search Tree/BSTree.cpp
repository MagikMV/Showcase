/* BSTree.cpp
 *
 * Binary search tree implementation
 */

 #include <iostream>
 #include "BSTree.h"

 using namespace std;


//  Constructor for a binary search tree
BST::BST()
 {
     root = NULL;
 }

//  Adding a node to the tree
void BST::AddNode(string title, string year, string actors[])
{
    node *n = new node;

    //  Populate data fields into new node
    n->title = title;
    n->year = year;
    for(int i = 0; i < 32; i++)
    {
        if(actors[i].empty())
        {
            break;
        }
        else
        {
            n->actors[i] = actors[i];
        }
    }
    n->left = NULL;
    n->right = NULL;

    //  Empty case
    if(root == NULL)
    {
        root = n;
    }
    //  Iterative Traversal
    else
    {
        node *temp = root;
        node *target;

        while(temp != NULL)
        {
            target = temp;

            //  Alphabetically before or equal
            if(title <= temp->title)
            {
                temp = temp->left;
            }
            //  Alphabetically after
            else
            {
                temp = temp->right;
            }
        }
        ////////////////////////////////////////////////////////
        //         NULL reached by temporary pointer          //
        //                                                    //
        // From target pointer, insert new node left or right //
        //                                                    //
              ////////////////// Left ///////////////////     //
        if(title <= target->title)                            //
        {                                                     //
            target->left = n;                                 //
        }                                                     //
              ////////////////// Right //////////////////     //
        else                                                  //
        {                                                     //
            target->right = n;                                //
        }                                                     //
        ////////////////////////////////////////////////////////
    }
}

//////////////////////////////////////////////////////
////////////////// PRIVATE METHODS ///////////////////
//////////////////////////////////////////////////////

//  1) Displaying all movie titles in alphabetical order
void BST::PrivateDisplayTitles(node *p)
{
    if(p != NULL)
    {
        PrivateDisplayTitles(p->left);
        cout << p->title << endl;
        PrivateDisplayTitles(p->right);
    }
}

//  2) Displaying actors of a given movie
void BST::PrivateDisplayActors(string titleKey, node *p)
{
    if(p != NULL)
    {
        if(titleKey <= p->title)
        {
            if(titleKey == p->title)
            {
                for(int i = 0; i < 32; i++)
                {
                    if(p->actors[i].empty())
                    {
                        break;
                    }
                    else
                    {
                        cout << p->actors[i] << endl;
                    }
                }
            }
            else
            {
                PrivateDisplayActors(titleKey, p->left);
            }
        }
        else
        {
            PrivateDisplayActors(titleKey, p->right);
        }
    }
}

//  3) Displaying movies of a given actor
void BST::PrivateActorsTitles(string actorKey, node *p)
{
    if(p != NULL)
    {
        PrivateActorsTitles(actorKey, p->left);
        for(int i = 0; i < 32; i++)
        {
            if(p->actors[i].empty())
            {
                break;
            }
            else
            {
                if(p->actors[i] == actorKey)
                {
                    cout << p->title << endl;
                }
            }
        }
        PrivateActorsTitles(actorKey, p->right);
    }
}

//  4) Displaying all movies released in a given year
void BST::PrivateYearsTitles(string yearKey, node *p)
{
    if(p != NULL)
    {
        PrivateYearsTitles(yearKey, p->left);
        if(p->year == yearKey)
        {
            cout << p->title << endl;
        }
        PrivateYearsTitles(yearKey, p->right);
    }
}

//////////////////////////////////////////////////////
////////////////// PUBLIC METHODS ////////////////////
//////////////////////////////////////////////////////

//  1) Call PrivateDisplayTitles
void BST::DisplayTitles()
{
    PrivateDisplayTitles(root);
}

//  2) Call PrivateDisplayActors
void BST::DisplayActors(string title)
{
    PrivateDisplayActors(title, root);
}

//  3) Call PrivateActorsTitles
void BST::DisplayActorsTitles(string actor)
{
    PrivateActorsTitles(actor, root);
}

//  4) Call PrivateYearsTitles
void BST::DisplayYearsTitles(string year)
{
    PrivateYearsTitles(year, root);
}
