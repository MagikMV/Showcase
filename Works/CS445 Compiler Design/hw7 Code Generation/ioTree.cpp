/* ioTree.cpp
 *
 * Miguel Villanueva
 * CS 445
 * March 27, 2021
 */

#include "ioTree.h"

//  Build IO tree
TreeNode *ioTree()
{
    TreeNode *cParam = ioNode(ParamK, Char, (char *)"dummy");
    TreeNode *bParam = ioNode(ParamK, Boolean, (char *)"dummy");
    TreeNode *Param = ioNode(ParamK, Integer, (char *)"dummy");

    TreeNode *outnl = ioNode(FuncK, Void, (char *)"outnl");
    TreeNode *outputc = ioNode(FuncK, Void, (char *)"outputc", outnl, cParam);
    TreeNode *outputb = ioNode(FuncK, Void, (char *)"outputb", outputc, bParam);
    TreeNode *output = ioNode(FuncK, Void, (char *)"output", outputb, Param);
    TreeNode *inputc = ioNode(FuncK, Char, (char *)"inputc", output);
    TreeNode *inputb = ioNode(FuncK, Boolean, (char *)"inputb", inputc);
    TreeNode *input = ioNode(FuncK, Integer, (char *)"input", inputb);

    return input;
}

//  Build IO node, for setting line number to -1
TreeNode *ioNode(DeclKind kind, ExpType type, char *name, TreeNode *sib, TreeNode *c0)
{
    TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
    if(t == NULL)
        printf("Out of memory error\n");
    else
    {
	for(int i = 0; i < MAXCHILDREN; i++)
            t->child[i] = NULL;

	if(c0 != NULL)
            t->child[0] = c0;
	
	t->sibling = NULL;
	if(sib != NULL)
	    t->sibling = sib;
	t->lineno = -1;
	t->attr.name = name;
	t->nodekind = DeclK;
        t->subkind.decl = kind;
	t->expType = type;
    }
    return t;
}

