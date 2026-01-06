/* semantic.h
 * 
 * Miguel Villanueva
 * March 10, 2021
 */

#ifndef _SEMANTIC_H_
#define _SEMANTIC_H_

#include "scantype.h"
#include "tree.h"
#include "symbolTable.h"

void semanticAnalysis(TreeNode *syntaxTree, SymbolTable *symbolTable);

//  Called By semanticAnalysis
void traverseTree(TreeNode *tree, SymbolTable *table);

#endif
