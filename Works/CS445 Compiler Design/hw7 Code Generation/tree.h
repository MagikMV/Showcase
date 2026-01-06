/* tree.h
 * 
 * Miguel Villanueva
 * CS 445
 * April 16, 2021
 */

#ifndef _TREE_H_
#define _TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "scantype.h"

extern int numErrors;

//  Kinds of Operators
//  these are the token numbers for the operators same as in flex
typedef int OpKind;

//  Kinds of Statements
enum NodeKind {DeclK, StmtK, ExpK};

//  Subkinds of Declarations
enum DeclKind {VarK, FuncK, ParamK};

//  Subkinds of Statements
enum StmtKind {NullK, IfK, WhileK, ForK, CompoundK, ReturnK, BreakK, RangeK};

//  Subkinds of Expressions
enum ExpKind {OpK, ConstantK, IdK, AssignK, InitK, CallK};

//  ExpType is used for type checking (Void means no type or value, UndefinedType means undefined)
enum ExpType {Void, Integer, Boolean, Char, CharInt, Equal, UndefinedType};

//  What kind of scoping is used?  (decided during typing)
enum VarKind {None, Local, Global, Parameter, LocalStatic};

#define MAXCHILDREN 3

struct TreeNode
{
    // connectivity in the tree
    TreeNode *child[MAXCHILDREN];          // children of the node
    TreeNode *sibling;                     // siblings for the node

    // what kind of node
    int lineno;                            // linenum relevant to this node
    NodeKind nodekind;                     // type of this node
    union                                  // subtype of type
    {
	DeclKind decl;                     // used when DeclK
	StmtKind stmt;                     // used when StmtK
	ExpKind exp;                       // used when ExpK
    } subkind;
    
    // extra properties about the node depending on type of the node
    union                                  // relevant data to type -> attr
    {
        OpKind op;                         // type of token (same as in bison)
	int value;                         // used when an integer constant or boolean
        unsigned char cvalue;              // used when a character
	char *string;                      // used when a string constant
	char *name;                        // used when IdK
    } attr;                                 
    ExpType expType;		           // used when ExpK for type checking
    bool isArray;                          // is this an array
    bool isStatic;                         // is staticly allocated?
    VarKind mem;
    int loc;
    int size;

    // even more semantic stuff will go here in later assignments.
    bool compoundFlag;
    bool used;
    bool boolOp;
    bool equals;
    bool unary;
    bool initialized;
    bool iChecked;
    bool arrayOp;
    bool sameCheck;
    bool suppressErrorMsg;
    bool boolbool;
    bool intInt;
    bool equalTypes;
    bool question;
};

TreeNode *newDeclNode(DeclKind kind,
                      ExpType type,
                      TokenData *token=NULL,
                      TreeNode *c0=NULL,
                      TreeNode *c1=NULL,
                      TreeNode *c2=NULL);  // save TokenData block!!

TreeNode *newStmtNode(StmtKind kind,
                      TokenData *token,
                      TreeNode *c0=NULL,
                      TreeNode *c1=NULL,
                      TreeNode *c2=NULL);

TreeNode *newExpNode(ExpKind kind,
                     TokenData *token,
                     TreeNode *c0=NULL,
                     TreeNode *c1=NULL,
                     TreeNode *c2=NULL);

//  Add a TreeNode to a list of siblings.
TreeNode *addSibling(TreeNode *t, TreeNode *s);

//  Pass the static and type attribute down the sibling list
void setType(TreeNode *t, ExpType type, bool isStatic);

//  Print memory (i.e. Local, Global, etc)
char *printMem(VarKind mem);

void printTree(TreeNode *tree, bool typesFlag, bool memFlag);

#endif
