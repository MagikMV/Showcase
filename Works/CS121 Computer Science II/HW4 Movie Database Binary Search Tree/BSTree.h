/* BSTree.h
 *
 * Interface for binary search tree class
 */

#ifndef BSTREE_H_INCLUDED
#define BSTREE_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

class BST
{
    private:
        struct node
        {
            string title;
            string year;
            string actors[32];
            node *left;
            node *right;
        };
        node *root;
        void PrivateDisplayTitles(node *p);
        void PrivateDisplayActors(string titleKey, node *p);
        void PrivateActorsTitles(string actorKey, node *p);
        void PrivateYearsTitles(string yearKey, node *p);

    public:
        BST();
        void AddNode(string title, string year, string actors[]);
        void DisplayTitles();
        void DisplayActors(string title);
        void DisplayActorsTitles(string actor);
        void DisplayYearsTitles(string year);
};

#endif // BSTREE_H_INCLUDED
