/* semantic.h
 * 
 * Miguel Villanueva
 * March 27, 2021
 */

#ifndef _SEMANTIC_H_
#define _SEMANTIC_H_

#include "tree.h"
#include "symbolTable.h"
#include "ioTree.h"

void semanticAnalysis(TreeNode *syntaxTree, SymbolTable *symbolTable);

//  Called by semanticAnalysis
void traverseTree(TreeNode *tree, SymbolTable *table);

//  Called by traverseTree
void checkIfUsed(std::string s, void *ptr);
char *checkExpType(ExpType expType);
void checkRange(TreeNode *tree, int i, int position, SymbolTable *table);
int countParams(TreeNode *first);
void checkParams(int callParams, int nodeParams, TreeNode *tree, TreeNode *node);

#endif
