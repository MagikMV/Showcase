/* ioTree.h
 * 
 * Miguel Villanueva
 * CS 445
 * March 27, 2021
 */

#ifndef _IOTREE_H_
#define _IOTREE_H_
#include "tree.h"

//  Build IO tree
TreeNode *ioTree();

//  Build IO node, for setting line number to -1
TreeNode *ioNode(DeclKind kind, ExpType type, char *name, TreeNode *sib=NULL, TreeNode *c0=NULL);

#endif
