/* codegen.h
 * 
 * Miguel Villanueva
 * CS 445
 * May 9, 2021
 */

#ifndef _CODEGEN_H_
#define _CODEGEN_H_

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <stack>
#include "tree.h"
#include "symbolTable.h"
#include "emitcode.h"

// Initialize Globals and Statics
void initGS(std::string s, void *ptr);

//  Traverses syntax tree, to emit TM code
void codegen(TreeNode *tree, SymbolTable *table);

//  Traverses I/O Library tree, to emit TM code
void codegenIO(TreeNode *tree);

//  Emits TM code for a given I/O Library tree node
void emitIO(TreeNode *n);

#endif
