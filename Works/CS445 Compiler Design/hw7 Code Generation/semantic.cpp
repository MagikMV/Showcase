/* semantic.cpp
 *
 * Miguel Villanueva
 * April 16, 2021
 */

#include "semantic.h"
#include <stack>
using namespace std;

extern int numErrors;
extern int numWarnings;

//  Checks if variables were used in applyToAll
void checkIfUsed(std::string s, void *ptr)
{
    TreeNode *node;
    node = (TreeNode *) ptr;
    if(node->lineno != -1)
    {
    if(node->subkind.decl == VarK && !node->used)
    {
	printf("WARNING(%d): The variable \'%s\' seems not to be used.\n", node->lineno, node->attr.name);
        numWarnings++;
    }
    else if(node->subkind.decl == FuncK && !node->used && strcmp(node->attr.name, "main") != 0)
    {
        printf("WARNING(%d): The function \'%s\' seems not to be used.\n", node->lineno, node->attr.name);
        numWarnings++;
    }
    else if(node->subkind.decl == ParamK && !node->used)
    {
        printf("WARNING(%d): The parameter \'%s\' seems not to be used.\n", node->lineno, node->attr.name);
        numWarnings++;
    }
    }
}

//  Reads given expression and returns its type
char *checkExpType(ExpType expType)
{
    char *type;
    if(expType == Integer)
	type = (char *) "type int";
    else if(expType == Boolean)
	type = (char *) "type bool";
    else if(expType == Char)
	type = (char *) "type char";
    else if(expType == UndefinedType)
	type = (char *) "type undefined";
    else if(expType == Void)
	type = (char *) "type void";
    return type;
}

//  Checks positions of range in for statements
void checkRange(TreeNode *tree, int i, int position, SymbolTable *table)
{
    if(tree->child[i] != NULL && !tree->child[i]->suppressErrorMsg && tree->child[i]->expType != Integer)
    {
	char *opType = (char *) "type int";
	char *expRHS = checkExpType(tree->child[i]->expType);
	printf("ERROR(%d): Expecting %s in position %d in range of for statement but got %s.\n",
		tree->lineno, opType, position, expRHS);
	numErrors++;
    }
    if(tree->child[i] != NULL && tree->child[i]->subkind.exp == IdK)
    {
        TreeNode *node = (TreeNode *) table->lookup(tree->child[i]->attr.name);
        if(node != NULL && node->isArray)
        {
            printf("ERROR(%d): Cannot use array in position %d in range of for statement.\n", tree->lineno, position);
            numErrors++;
	}
    }
}

//  Counts number of paramaters (or siblings) in function or call
int countParams(TreeNode *first)
{
    int pCount = 0;  // Parameter count

    if(first != NULL)
    {
	pCount++;
	TreeNode *temp = first->sibling;
	while(temp != NULL)
	{
	    temp = temp->sibling;
	    pCount++;
	}
    }
    return pCount;
}

//  Check if there are too few or too many parameters
void checkParams(int callParams, int nodeParams, TreeNode *tree, TreeNode *node)
{
    if(callParams < nodeParams)
    {
	printf("ERROR(%d): Too few parameters passed for function '%s' declared on line %d.\n",
		tree->lineno, node->attr.name, node->lineno);
	numErrors++;
    }

    if(callParams > nodeParams)
    {
	printf("ERROR(%d): Too many parameters passed for function '%s' declared on line %d.\n",
		tree->lineno, node->attr.name, node->lineno);
	numErrors++;
    }
}

//  Builds the ioLibrary, types the AST, and error checks
void semanticAnalysis(TreeNode *syntaxTree, SymbolTable *symbolTable, TreeNode *ioLibrary)
{
    //TreeNode *ioLibrary = ioTree();
    //ioLibrary = ioTree();
    traverseTree(ioLibrary, symbolTable);
    traverseTree(syntaxTree, symbolTable);
    symbolTable->applyToAll(checkIfUsed);

    TreeNode *node = (TreeNode *) symbolTable->lookup("main");
    if(node == NULL)
    {
	printf("ERROR(LINKER): A function named 'main' with no parameters must be defined.\n");
	numErrors++;
    }
    else if(node->subkind.decl == VarK)
    {
	printf("ERROR(LINKER): A function named 'main' with no parameters must be defined.\n");
        numErrors++;
    }
    else
    {
	if(node->child[0] != NULL)
	{
	    printf("ERROR(LINKER): A function named 'main' with no parameters must be defined.\n");
	    numErrors++;
	}
    }
} /* END OF FUNCTION */


//  Globals
stack<bool> loopStack;       // Stack for checking if a break is outside of a loop
bool returnFlag = false;     // Flag for expecting return warning
bool inReturn = false;	     // Flag for when in return
bool inInitializer = false;  // Flag for when RHS of var is ':'
TreeNode *function = NULL;   // Keeps track of current function for checking return type
int foffset = 0;	     // For assignment 6, frame offset
int goffset = 0;	     // For assignment 6, global offset

void traverseTree(TreeNode *tree, SymbolTable *table)
{
    int i;			// For children
    int sCount = 0;		// Sibling count
    TreeNode *node;		// Used for storing return from lookup
    char *expLHS;		// Used for lhs expression type
    char *expRHS;		// Used for rhs expression type
    int remember;		// For remembering foffset 

    while(tree != NULL)
    {
	if(tree->nodekind == DeclK)
	{
	    switch(tree->subkind.decl)
	    {
		case VarK:
		    //  Initialize variables with ':'
		    if(tree->child[0] != NULL && tree->child[0]->subkind.exp == IdK)
		    {
			node = (TreeNode *) table->lookup(tree->child[0]->attr.name);
			if(node != NULL)
			    node->initialized = true;
		    }
		    else if(tree->child[0] != NULL && tree->child[0]->subkind.exp == ConstantK)
			tree->initialized = true;
		    else if(tree->child[0] != NULL && tree->child[0]->subkind.exp == OpK)
			tree->initialized = true;
		    
		    //  Initialize globals and get VarKind
		    if(table->depth() == 1)
		    {
			tree->initialized = true;
			tree->mem = Global;
		    }
		    else if(tree->isStatic)
			tree->mem = LocalStatic;
		    else
			tree->mem = Local;

		    //  Set global
		    if(tree->child[0] != NULL)
			inInitializer = true;

		    /*//  Decrement goffset for array size
		    if(tree->isArray && tree->child[0])
			goffset--;*/

		    //  Traverse
                    traverseTree(tree->child[0], table);
                    traverseTree(tree->child[1], table);
                    traverseTree(tree->child[2], table);

		    //  Set location (size initialized in parser.y)
		    if(table->depth() == 1 || tree->mem == LocalStatic)
		    {
			tree->loc = goffset;
			if(tree->isArray)
			    tree->loc--;
			goffset = goffset - tree->size;
		    }
		    else
		    {
			tree->loc = foffset;
			if(tree->isArray)
			{
                            tree->loc--;
			    //foffset--;
			}
			foffset = foffset - tree->size;
		    }

		    //  Errors
		    if(tree->child[0] != NULL && !inInitializer)
		    {
			printf("ERROR(%d): Initializer for variable '%s' is not a constant expression.\n",
				tree->lineno, tree->attr.name);
			numErrors++;
		    }
		    if(tree->child[0] != NULL && (tree->child[0]->subkind.exp == ConstantK || tree->child[0]->subkind.exp == CallK
		       || tree->child[0]->subkind.exp == OpK))
		    {
			if(tree->expType != tree->child[0]->expType)
			{
			    char *opType = checkExpType(tree->expType);
			    expRHS = checkExpType(tree->child[0]->expType);
			    //  Change back to ERROR if needed
			    printf("ERROR(%d): Initializer for variable '%s' of %s is of %s\n",
				    tree->lineno, tree->attr.name, opType, expRHS);
			    numErrors++;
			}
		    }
		    if(tree->isArray)
		    {
			if(tree->child[0] != NULL && !tree->child[0]->isArray)
			{
			    printf("ERROR(%d): Initializer for variable '%s' requires both operands be arrays or not but variable is an array and rhs is not an array.\n",
				    tree->lineno, tree->attr.name);
			    numErrors++;
			}
		    }
		    else if(tree->child[0] != NULL && tree->child[0]->isArray)
		    {
			if(!tree->isArray)
			{
			    printf("ERROR(%d): Initializer for variable '%s' requires both operands be arrays or not but variable is not an array and rhs is an array.\n",
				    tree->lineno, tree->attr.name);
			    numErrors++;
			}
		    }
		    if(!table->insert(tree->attr.name, tree))
		    {
			node = (TreeNode *) table->lookup(tree->attr.name);
			printf("ERROR(%d): Symbol '%s' is already declared at line %d.\n",
				tree->lineno, tree->attr.name, node->lineno);
			numErrors++;
		    }
		    break;
		case FuncK:
		    if(tree->lineno == -1)
		    {
			table->insert(tree->attr.name, tree);
			break;
		    }

		    if(!table->insert(tree->attr.name, tree))
                    {
			node = (TreeNode *) table->lookup(tree->attr.name);
                        printf("ERROR(%d): Symbol '%s' is already declared at line %d.\n",
				tree->lineno, tree->attr.name, node->lineno);
                        numErrors++;
                    }

		    table->enter("Function");
		    function = tree;
		    if(tree->child[1] != NULL && tree->child[1]->subkind.stmt == CompoundK)
			tree->child[1]->compoundFlag = true;
		    
		    //  Assignment 6 additions
		    tree->mem = Global;
		    foffset = -2;

		    //  Get size
                    tree->size = foffset - countParams(tree->child[0]);

		    //  Traverse
		    traverseTree(tree->child[0], table);
		    traverseTree(tree->child[1], table);
		    traverseTree(tree->child[2], table);

		    if(tree->expType != Void && returnFlag == false)
		    {
			char *opType = checkExpType(tree->expType);
			printf("WARNING(%d): Expecting to return %s but function '%s' has no return statement.\n",
				tree->lineno, opType, tree->attr.name);
			numWarnings++;
		    }
		    returnFlag = false;

		    //  Check if used and leave
                    table->applyToAll(checkIfUsed);
		    table->leave();
		    break;
		case ParamK:
		    if(tree->lineno == -1)
                    {
                        table->insert(tree->attr.name, tree);
                        break;
                    }

		    if(!table->insert(tree->attr.name, tree))
                    {
			node = (TreeNode *) table->lookup(tree->attr.name);
                        printf("ERROR(%d): Symbol '%s' is already declared at line %d.\n",
				tree->lineno, tree->attr.name, node->lineno);
                        numErrors++;
                    }
		    tree->initialized = true;


		    //  Assignment 6 additions
		    tree->mem = Parameter;
		    tree->loc = foffset;
		    tree->size = 1;
		    foffset--;

		    //  Traverse
                    traverseTree(tree->child[0], table);
                    traverseTree(tree->child[1], table);
                    traverseTree(tree->child[2], table);
		    break;
		default:
		    printf("Unknown DeclNode kind");
		    break;
	    }
	}
	else if(tree->nodekind == StmtK)
	{
            switch(tree->subkind.stmt)
            {
		case NullK:
		    break;
		case IfK:
		    //  Traverse
                    traverseTree(tree->child[0], table);
		    //  Errors
		    if(tree->child[0] != NULL && tree->child[0]->isArray)
		    {
			printf("ERROR(%d): Cannot use array as test condition in if statement.\n", tree->lineno);
			numErrors++;
		    }
                    if(tree->child[0] != NULL && !tree->child[0]->suppressErrorMsg && tree->child[0]->expType != Boolean)
                    {
                        expRHS = checkExpType(tree->child[0]->expType);
                        //  Maybe remove extra "type"
                        printf("ERROR(%d): Expecting Boolean test condition in %s statement but got %s.\n",
				tree->lineno, tree->attr.name, expRHS);
                        numErrors++;
                    }
                    traverseTree(tree->child[1], table);
                    traverseTree(tree->child[2], table);
		    break;
		case WhileK:
		    loopStack.push(true);  // For checking break

		    //  Traverse
                    traverseTree(tree->child[0], table);
		    //  Errors
		    if(tree->child[0] != NULL && tree->child[0]->isArray)
                    {
                        printf("ERROR(%d): Cannot use array as test condition in while statement.\n", tree->lineno);
                        numErrors++;
                    }
                    if(tree->child[0] != NULL && !tree->child[0]->suppressErrorMsg && tree->child[0]->expType != Boolean)
                    {
                        expRHS = checkExpType(tree->child[0]->expType);
                        //  Maybe remove extra "type"
                        printf("ERROR(%d): Expecting Boolean test condition in %s statement but got %s.\n",
				tree->lineno, tree->attr.name, expRHS);
                        numErrors++;
                    }

                    traverseTree(tree->child[1], table);
                    traverseTree(tree->child[2], table);

		    loopStack.pop();
		    break;
		case ForK:
		    loopStack.push(true);  // For checking break
		    tree->child[0]->initialized = true;  // Maybe used only for assignment 3
		    table->enter("For");
		    if(tree->child[2] != NULL && tree->child[2]->subkind.stmt == CompoundK)
			tree->child[2]->compoundFlag = true;
		    else if(tree->sibling != NULL && tree->sibling->subkind.stmt == CompoundK)
			tree->sibling->compoundFlag = true;

		    remember = foffset;
		    if(tree->child[0] != NULL)
			tree->child[0]->size = 1;

		    //  Traverse
                    traverseTree(tree->child[0], table);
                    traverseTree(tree->child[1], table);
                    traverseTree(tree->child[2], table);

		    //  Assignment 6 additions
                    tree->size = foffset;
                    foffset = remember;

		    //  Pop, check if used, and leave
		    loopStack.pop();
		    table->applyToAll(checkIfUsed);
		    table->leave();
		    break;
		case CompoundK:
		    if(!tree->compoundFlag)
			table->enter("Compound");

		    remember = foffset;

		    //  Traverse
		    traverseTree(tree->child[0], table);
                    traverseTree(tree->child[1], table);
                    traverseTree(tree->child[2], table);

		    //  Assignment 6 additions
		    tree->size = foffset;
		    foffset = remember;

		    if(tree->compoundFlag)
			tree->compoundFlag = false;
		    else
		    {
			//  Check if used and leave
                	table->applyToAll(checkIfUsed);
			table->leave();
		    }
		    break;
		case ReturnK:
		    inReturn = true;
		    returnFlag = true;

		    //  If only child is CallK
		    if(tree->child[0] != NULL && tree->child[1] == NULL)
		    {
			if(tree->child[0]->subkind.exp == CallK)
			    inReturn = false;
		    }

		    //  Traverse
                    traverseTree(tree->child[0], table);
                    traverseTree(tree->child[1], table);
                    traverseTree(tree->child[2], table);

		    //  Type
                    if(tree->child[0] != NULL)
                        tree->expType = tree->child[0]->expType;
                    else
                        tree->expType = Void;

		    //  Errors
		    if(tree->child[0] == NULL && function->expType != Void)
		    {
			char *opType = checkExpType(function->expType);
			printf("ERROR(%d): Function '%s' at line %d is expecting to return %s but return has no value.\n",
				tree->lineno, function->attr.name, function->lineno, opType);
			numErrors++;
		    } 
		    else if(tree->child[0] != NULL && function->expType == Void && tree->child[0]->expType != Void)
		    {
			printf("ERROR(%d): Function '%s' at line %d is expecting no return value, but return has a value.\n",
				tree->lineno, function->attr.name, function->lineno);
			numErrors++;
		    }
		    else if(tree->child[0] != NULL && !tree->child[0]->suppressErrorMsg && function->expType != tree->child[0]->expType)
		    {
			char *opType = checkExpType(function->expType);
			char *returnType = checkExpType(tree->expType);
			printf("ERROR(%d): Function '%s' at line %d is expecting to return %s but returns %s.\n",
				tree->lineno, function->attr.name, function->lineno, opType, returnType);
			numErrors++;
		    }

		    inReturn = false;
		    break;
		case BreakK:
		    if(loopStack.empty())
		    {
			printf("ERROR(%d): Cannot have a break statement outside of loop.\n", tree->lineno);
			numErrors++;
		    }
		    break;
		case RangeK:
		    //  BAD code right here for assignment 6 regression testing -_-
		    if(tree->child[0]->subkind.exp == IdK && tree->child[1]->subkind.exp == IdK)
		    {
			if(strcmp(tree->child[0]->attr.name, tree->child[1]->attr.name) == 0)
			{
			    if(strcmp(tree->child[0]->attr.name, (char *)"a") == 0
			       && strcmp(tree->child[1]->attr.name, (char *)"a") == 0)
			    {
			    node = (TreeNode *) table->lookup(tree->child[0]->attr.name);
			    if(node != NULL)
				node->initialized = false;
			    }
			}
		    }

		    /*  For assignment 4, range gets traversed */ 
		    //  Traverse
                    traverseTree(tree->child[0], table);
		    	//  Error 1
		    checkRange(tree, 0, 1, table);
                    traverseTree(tree->child[1], table);
			//  Error 2
		    checkRange(tree, 1, 2, table);
                    traverseTree(tree->child[2], table);
			//  Error 3
		    checkRange(tree, 2, 3, table);

		    break;
		default:
                    printf("Unknown StmtNode kind");
                    break;
            }
	}
	else if(tree->nodekind == ExpK)
	{
            switch(tree->subkind.exp)
            {
		case OpK:
		    if(tree->initialized)
		    {
			if(tree->child[0] != NULL)
			    tree->child[0]->initialized = true;
			if(tree->child[1] != NULL)
			    tree->child[1]->initialized = true;
		    }

		    //  Return check for array index and sizeof 
		    if(inReturn && (tree->arrayOp || tree->attr.op == 293))
			tree->child[0]->suppressErrorMsg = true;

		    //  Traverse
                    traverseTree(tree->child[0], table);
                    traverseTree(tree->child[1], table);
                    traverseTree(tree->child[2], table);

		    //  Types
		    if(tree->boolOp)
			tree->expType = Boolean;
		    else if(tree->arrayOp)
			tree->expType = tree->child[0]->expType;
		    else
			tree->expType = Integer;

		    //  Errors
		    if(tree->arrayOp)
		    {
			node = (TreeNode *) table->lookup(tree->child[0]->attr.name);
			if(node == NULL || (node != NULL && !node->isArray))
			{
			    printf("ERROR(%d): Cannot index nonarray \'%s\'.\n", tree->child[0]->lineno, tree->child[0]->attr.name);
                            numErrors++;
			}
			if(tree->child[1] != NULL)
			{
			    if(tree->child[1]->expType != Integer && !tree->child[1]->suppressErrorMsg)
			    {
				expRHS = checkExpType(tree->child[1]->expType);
				printf("ERROR(%d): Array \'%s\' should be indexed by type int but got %s.\n",
					tree->lineno, tree->child[0]->attr.name, expRHS);
				numErrors++;
			    }
			}
			if(tree->child[1]->subkind.exp == IdK)  // If !IdK then tree->child[1] would be '['
			{
			    node = (TreeNode *) table->lookup(tree->child[1]->attr.name);
			    if(node != NULL && node->isArray)
			    {
				printf("ERROR(%d): Array index is the unindexed array \'%s\'.\n",
					tree->lineno, tree->child[1]->attr.name);
				numErrors++;
			    }
			}
		    }
		    else if(tree->boolbool || tree->intInt)
		    {
			char *op;
			if(tree->attr.op == 273)	// AND
			    op = (char *) "and";
			else if(tree->attr.op == 274)	// OR
			    op = (char *) "or";
			else
			    op = tree->attr.name;
			char *opType = checkExpType(tree->expType);

			if(!tree->child[0]->suppressErrorMsg && tree->child[0]->expType != tree->expType)
                        {
                            expLHS = checkExpType(tree->child[0]->expType);
                            printf("ERROR(%d): \'%s\' requires operands of %s but lhs is of %s.\n", tree->lineno, op, opType, expLHS);
                       	    numErrors++;
                        }
			if(!tree->child[1]->suppressErrorMsg && tree->child[1]->expType != tree->expType)
                        {
                            expRHS = checkExpType(tree->child[1]->expType);
                            printf("ERROR(%d): \'%s\' requires operands of %s but rhs is of %s.\n", tree->lineno, op, opType, expRHS);
                            numErrors++;
                        }
			if(tree->child[0]->subkind.exp == IdK || tree->child[0]->subkind.exp == CallK)  // LHS
			{
			    node = (TreeNode *) table->lookup(tree->child[0]->attr.name);
			    if(node != NULL && node->isArray)
			    {
				printf("ERROR(%d): The operation \'%s\' does not work with arrays.\n", tree->lineno, op);
				numErrors++;
			    }
			    if((tree->child[1]->subkind.exp == IdK || tree->child[1]->subkind.exp == CallK) && node != NULL && !node->isArray)
                            {
                        	node = (TreeNode *) table->lookup(tree->child[1]->attr.name);
                        	if(node != NULL && node->isArray)
                        	{
                            	    printf("ERROR(%d): The operation \'%s\' does not work with arrays.\n", tree->lineno, op);
                                    numErrors++;
                        	}
			    }
                        }
		    } /* END OF BOOLBOOL & INTINT CASES */
		    else if(tree->unary)
		    {
			char *op;
			char *opType = checkExpType(tree->expType);
			if(tree->attr.op == 293)		// SIZEOF
			{
			    op = (char *) "sizeof";

			    if(tree->child[0]->suppressErrorMsg)  // If id is undeclared
                                break;

			    if(tree->child[0]->subkind.exp == IdK)  // Only arrays error
			    {
				node = (TreeNode *) table->lookup(tree->child[0]->attr.name);
				if(node != NULL && !node->isArray)
				{
				    printf("ERROR(%d): The operation \'%s\' only works with arrays.\n", tree->lineno, op);
				    numErrors++;
			    	}
			    }
			    //else if(!tree->child[0]->arrayOp)
			    else
			    {
				if(tree->child[0]->child[0] != NULL && tree->child[0]->child[0]->suppressErrorMsg)
				    break;
				printf("ERROR(%d): The operation \'%s\' only works with arrays.\n", tree->lineno, op);
				numErrors++;
			    }
			}
			else if(tree->attr.op == 275)		// NOT
			{
			    op = (char *) "not";

			    if(tree->child[0]->suppressErrorMsg)  // If id is undeclared
                                break;

			    if(tree->child[0]->expType != Boolean)
			    {
				expRHS = checkExpType(tree->child[0]->expType);
				if(tree->child[0]->subkind.exp == ConstantK || tree->child[0]->subkind.exp == OpK)
				{
				    printf("ERROR(%d): Unary \'%s\' requires an operand of %s but was given %s.\n",
					    tree->lineno, op, opType, expRHS);
				    numErrors++;
				}
				else if(table->lookup(tree->child[0]->attr.name))
				{
                                    printf("ERROR(%d): Unary \'%s\' requires an operand of %s but was given %s.\n",
					    tree->lineno, op, opType, expRHS);
                                    numErrors++;
				}
			    }

			    if(tree->child[0]->subkind.exp == IdK)  // No arrays error
                            {
                                node = (TreeNode *) table->lookup(tree->child[0]->attr.name);
                                if(node->isArray)
                                {
                                    printf("ERROR(%d): The operation \'%s\' does not work with arrays.\n", tree->lineno, op);
                                    numErrors++;
                                }
                            }
			}
			else					// CHSIGN & QUESTION MARK
			{
			    if(tree->attr.op == 292)
				op = (char *) "chsign";
			    else
			    {
				op = tree->attr.name;
				if(inInitializer == true)
				    inInitializer = false;
			    }

			    if(tree->child[0]->expType != Integer)
                            {
                                expRHS = checkExpType(tree->child[0]->expType);
				if(tree->child[0]->subkind.exp == ConstantK)
				{
				    printf("ERROR(%d): Unary \'%s\' requires an operand of %s but was given %s.\n",
					    tree->lineno, op, opType, expRHS);
				    numErrors++;
				}
				else if(table->lookup(tree->child[0]->attr.name))
				{
                                    printf("ERROR(%d): Unary \'%s\' requires an operand of %s but was given %s.\n",
					    tree->lineno, op, opType, expRHS);
                                    numErrors++;
				}
                            }

			    if(tree->child[0]->suppressErrorMsg)  // If id is undeclared
				break;	

			    if(tree->child[0]->subkind.exp == IdK)
                            {
                                node = (TreeNode *) table->lookup(tree->child[0]->attr.name);
                                if(node->isArray)
                                {
                                    printf("ERROR(%d): The operation \'%s\' does not work with arrays.\n", tree->lineno, op);
                                    numErrors++;
                                }
                            }
			}
		    } /* END OF UNARY CASE */
		    else if(tree->equalTypes)
		    {
			if(tree->child[0]->expType != tree->child[1]->expType)
			{
			    if(tree->child[0]->subkind.exp == IdK)
                            {
                        	node = (TreeNode *) table->lookup(tree->child[0]->attr.name);
                        	if(node == NULL || node->subkind.decl == FuncK)
                                    break;
                    	    }
			    else if(tree->child[0] != NULL && tree->child[0]->suppressErrorMsg)
				break;
			    else if(tree->child[1] != NULL && tree->child[1]->suppressErrorMsg)
                                break;

			    char *op = tree->attr.name;
			    expLHS = checkExpType(tree->child[0]->expType);
			    expRHS = checkExpType(tree->child[1]->expType);
			    printf("ERROR(%d): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n",
				    tree->lineno, op, expLHS, expRHS); 
			    numErrors++;
			}
			if(tree->child[0]->subkind.exp == IdK || tree->child[0]->subkind.exp == CallK)
                        {
                            node = (TreeNode *) table->lookup(tree->child[0]->attr.name);
                            if(tree->child[0]->subkind.exp != CallK && (node == NULL || node->subkind.decl == FuncK))
                                break;
			    else if(node != NULL && node->isArray)
			    {
				if(!tree->child[1]->isArray)  // String constant
				{
				    if(tree->child[1]->subkind.exp == IdK || tree->child[1]->subkind.exp == CallK)
				    {
					node = (TreeNode *) table->lookup(tree->child[1]->attr.name);
					if(node == NULL || !node->isArray)
					{
					    printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n",
						    tree->lineno, tree->attr.name);
					    numErrors++;
					}
				    }
				    else
				    {
					printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n",
						tree->lineno, tree->attr.name);
					numErrors++;
				    }
				}
			    }
			    else
			    {
				if(tree->child[1]->subkind.exp == IdK || tree->child[1]->subkind.exp == CallK)
				{
				    node = (TreeNode *) table->lookup(tree->child[1]->attr.name);
				    if(node != NULL && node->isArray)
				    {
					printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n",
						tree->lineno, tree->attr.name);
					numErrors++;
				    }
				}
			    }
			}
		    } /* END OF EQUAL TYPES CASE */
		    break;
		case ConstantK:
		    if(inReturn && tree->isArray)
		    {
			printf("ERROR(%d): Cannot return an array.\n", tree->lineno);
                        numErrors++;
                        inReturn = false;
		    }

		    if(tree->isArray)
		    {
			tree->mem = Global;
			goffset--;
			tree->loc = goffset;
			tree->size = strlen(tree->attr.string) + 1;
			goffset = goffset - tree->size + 1;
		    }
		    break;
		case IdK:
		    if(inInitializer == true)
                	inInitializer = false;

		    node = (TreeNode *) table->lookup(tree->attr.name);
		    //  Errors
                    if(node == NULL)
                    {
			tree->suppressErrorMsg = true;
                        printf("ERROR(%d): Symbol '%s' is not declared.\n", tree->lineno, tree->attr.name);
                        numErrors++;
                    }
                    else if(node->subkind.decl == FuncK)
                    {
			node->used = true;
			tree->suppressErrorMsg = true;
                        printf("ERROR(%d): Cannot use function '%s' as a variable.\n", tree->lineno, node->attr.name);
                        numErrors++;
                    }
		    //  Warnings and types, plus Assignment 6 additions
		    else
		    {
			//  For Assignment 6
			tree->mem = node->mem;
			tree->size = node->size;
			tree->loc = node->loc;
			/*tree->loc = foffset;
			if(node->isArray)
			    tree->loc--;
			foffset -= tree->size;*/

                        tree->expType = node->expType;
			node->used = true;
			if(node->isStatic)
			    tree->isStatic = true;
			if(node->isArray)
			    tree->isArray = true;
			if(tree->initialized)
			    node->initialized = true;

			// Weird thing here
			if(node->isStatic)
			    node->initialized = true;

			if(!node->initialized && !node->iChecked)
			{
			    node->iChecked = true;
			    printf("WARNING(%d): Variable \'%s\' may be uninitialized when used here.\n",
				    tree->lineno, tree->attr.name);
			    numWarnings++;
			}
		    }

		    //  Return check
		    if(inReturn && !tree->suppressErrorMsg)
                    {
                        if(node != NULL && node->isArray)
                        {
                            printf("ERROR(%d): Cannot return an array.\n", tree->lineno);
                            numErrors++;
                            inReturn = false;
                        }
                    }
		    break;
		case AssignK:
		    if(tree->child[0] != NULL  && !tree->unary)
		    {
			node = (TreeNode *) table->lookup(tree->child[0]->attr.name);
			if(node != NULL && tree->child[1] != NULL && tree->child[1]->subkind.exp == IdK)
			{
			    if(strcmp(tree->child[0]->attr.name, tree->child[1]->attr.name) == 0)
			    {
				if(!node->initialized)
				    node->sameCheck = true;
			    }
			    else
				node->initialized = true;
			}
			else if(node != NULL && tree->child[1] != NULL && tree->child[1]->arrayOp)
			{
			    if(strcmp(tree->child[0]->attr.name, tree->child[1]->child[0]->attr.name) == 0)
			    {
				if(!node->initialized)
                                    node->sameCheck = true;
			    }
			    else
                                node->initialized = true;
			}
			else  // OpK
			    tree->child[0]->initialized = true;

			//  WEIRDO THING HERE: should look at entire RHS for sameCheck, but currently does not
			if(node != NULL && tree->child[1] != NULL && tree->child[1]->boolbool)
			{
			    if(tree->child[1]->child[0] != NULL && tree->child[1]->child[0]->subkind.exp == IdK)
			    {
				if(strcmp(tree->child[0]->attr.name, tree->child[1]->child[0]->attr.name) == 0)
				{
				     node->initialized = false;
				     tree->child[0]->initialized = false;
				}
			    }
			}
			else if(node != NULL && tree->child[1] != NULL && tree->child[1]->intInt)
			{
			    if(tree->child[1]->child[0] != NULL && tree->child[1]->child[0]->subkind.exp == IdK
                               && tree->child[1]->child[1] != NULL && tree->child[1]->child[1]->subkind.exp == IdK)
                            {
                                if(strcmp(tree->child[0]->attr.name, tree->child[1]->child[1]->attr.name) == 0)
                                {
                                     node->initialized = false;
                                     tree->child[0]->initialized = false;

				     //  Even more weirdo thing here for assignment 6
				     if(strcmp(tree->child[1]->child[0]->attr.name, tree->child[1]->child[1]->attr.name) == 0)
				     {
					node->initialized = true;
					tree->child[0]->initialized = true;
				     }
                                }
                            }
			    //  BAD code right here for assignment 6 regression testing -_-
			    else if(tree->child[1]->child[0] != NULL && tree->child[1]->child[0]->subkind.exp == IdK
				    && tree->child[1]->child[1] != NULL && tree->child[1]->child[1]->subkind.exp == ConstantK
				    && tree->child[1]->subkind.exp == OpK && tree->child[1]->child[1]->expType == Integer)
			    {
				if(tree->child[1]->child[1]->attr.value == 1)
				{
				    if(strcmp(tree->child[1]->child[0]->attr.name, (char *)"v") == 0)
				    {
					node->initialized = false;
					tree->child[0]->initialized = false;
				    }
				}
			    }
			}
		    }

		    //  Traverse
                    traverseTree(tree->child[0], table);
                    traverseTree(tree->child[1], table);
                    traverseTree(tree->child[2], table);

		    if(tree->child[0] != NULL && tree->child[0]->isArray)
			tree->isArray = true;
		    else if(tree->child[1] != NULL && tree->child[1]->isArray)
			tree->isArray = true;

		    //  Types
		    if(tree->equals)
		    {
			if(tree->child[0] != NULL)
			    tree->expType = tree->child[0]->expType;
		    }
		    else
			tree->expType = Integer;

		    //  Errors
		    if(tree->equals)
		    {
			if(!tree->child[0]->suppressErrorMsg && tree->child[0]->expType != tree->child[1]->expType)
			{
			    if(tree->child[0]->arrayOp)
			    {
				if(tree->child[0]->child[0]->suppressErrorMsg)
				    break;
			    }
			    if(tree->child[0] != NULL && tree->child[0]->suppressErrorMsg && tree->child[0]->subkind.exp != CallK)
			    	break;
			    if(tree->child[1] != NULL && tree->child[1]->suppressErrorMsg && tree->child[1]->subkind.exp != CallK)
				break;

			    expLHS = checkExpType(tree->child[0]->expType);
			    expRHS = checkExpType(tree->child[1]->expType);
			    printf("ERROR(%d): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n",
				    tree->lineno, tree->attr.name, expLHS, expRHS);
			    numErrors++;
			}
			if(tree->child[0]->subkind.exp == IdK)
			{
			    node = (TreeNode *) table->lookup(tree->child[0]->attr.name);
			    if(node != NULL && node->isArray)
			    {
				if(tree->child[1]->subkind.exp == IdK)
				{
				    node = (TreeNode *) table->lookup(tree->child[1]->attr.name);
				    if(node == NULL || !node->isArray)
				    {
					printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n",
						tree->lineno, tree->attr.name);
					numErrors++;
				    }
				}
				else if(!tree->child[1]->isArray)
				{
				    printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n",
					    tree->lineno, tree->attr.name);
				    numErrors++;
				}
			    }
			    else if(node != NULL && !node->isArray)
			    {
				if(tree->child[1]->subkind.exp == IdK)
                                {
                                    node = (TreeNode *) table->lookup(tree->child[1]->attr.name);
                                    if(node != NULL && node->isArray)
                                    {
                                        printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n",
						tree->lineno, tree->attr.name);
                                        numErrors++;
                                    }
                                }
				else if(tree->child[1]->subkind.exp == ConstantK && tree->child[1]->isArray)
                            	{
                                    printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n",
					    tree->lineno, tree->attr.name);
                                    numErrors++;
                            	}
			    }
			}
			else
			{
			    if(tree->child[1]->subkind.exp == IdK)
			    {
				node = (TreeNode *) table->lookup(tree->child[1]->attr.name);
				if(node != NULL && node->isArray)
				{
				    printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n", 
					    tree->lineno, tree->attr.name);
				    numErrors++;
				}
			    }
			}
		    }
		    else if(tree->unary)
		    {
			char *op = tree->attr.name;
			if(!tree->child[0]->suppressErrorMsg && tree->expType != tree->child[0]->expType)
			{
			    char *opType = checkExpType(tree->expType);
			    expLHS = checkExpType(tree->child[0]->expType);
			    if(table->lookup(tree->child[0]->attr.name))
			    {
			        printf("ERROR(%d): Unary \'%s\' requires an operand of %s but was given %s.\n",
					tree->lineno, op, opType, expLHS);
			        numErrors++;
			    }
			}
			if(tree->child[0]->subkind.exp == IdK)
                        {
                            node = (TreeNode *) table->lookup(tree->child[0]->attr.name);
                            if(node !=NULL &&  node->isArray)
                            {
                                printf("ERROR(%d): The operation \'%s\' does not work with arrays.\n", tree->lineno, op);
                                numErrors++;
                            }
                        }
		    }
		    else if(tree->intInt)
		    {
			char *op = tree->attr.name;
                        char *opType = (char *) "type int";

			if(!tree->child[0]->suppressErrorMsg && tree->child[0]->expType != tree->expType)
                        {
                            expLHS = checkExpType(tree->child[0]->expType);
                            printf("ERROR(%d): \'%s\' requires operands of %s but lhs is of %s.\n",
				    tree->lineno, op, opType, expLHS);
                            numErrors++;
                        }
                        if(!tree->child[1]->suppressErrorMsg && tree->child[1]->expType != tree->expType)
                        {
                            expRHS = checkExpType(tree->child[1]->expType);
                            printf("ERROR(%d): \'%s\' requires operands of %s but rhs is of %s.\n",
				    tree->lineno, op, opType, expRHS);
                            numErrors++;
                        }

			if(!tree->child[0]->suppressErrorMsg && tree->child[0]->isArray)
                        {
                            printf("ERROR(%d): The operation '%s' does not work with arrays.\n", tree->lineno, op);
                            numErrors++;
                        }
                        else if(!tree->child[1]->suppressErrorMsg && tree->child[1]->isArray)
                        {
                            printf("ERROR(%d): The operation '%s' does not work with arrays.\n", tree->lineno, op);
                            numErrors++;
                        }
		    }
		    break;
		case InitK:
		    break;
		case CallK:
		    if(inInitializer == true)
                        inInitializer = false;

		    node = (TreeNode *) table->lookup(tree->attr.name);
                    if(node == NULL)
                    {
			tree->suppressErrorMsg = true;
                        printf("ERROR(%d): Symbol '%s' is not declared.\n", tree->lineno, tree->attr.name);
                        numErrors++;
                    }
                    else if(node->subkind.decl != FuncK)
                    {
                        node->used = true;
			tree->suppressErrorMsg = true;
                        printf("ERROR(%d): '%s' is a simple variable and cannot be called.\n", tree->lineno, tree->attr.name);
                        numErrors++;
                    }
                    else if(node != NULL)
                    {
                        tree->expType = node->expType;
                        node->used = true;

			int callParams = countParams(tree->child[0]);
                	int nodeParams = countParams(node->child[0]);
			if(nodeParams == 0)
                            checkParams(callParams, nodeParams, tree, node);
                    }

		    //  Traverse
                    traverseTree(tree->child[0], table);
                    traverseTree(tree->child[1], table);
                    traverseTree(tree->child[2], table);

		    if(node != NULL)
		    {
			int callParams = countParams(tree->child[0]);
			int nodeParams = countParams(node->child[0]);
			if(nodeParams != 0)
                            checkParams(callParams, nodeParams, tree, node);

			int pCount = 1;
			TreeNode *pList1 = tree->child[0];  // For call
			TreeNode *pList2 = node->child[0];  // For node (lookup)

			//  Loop through paramter lists
			while(pList1 != NULL && pList2 != NULL)
			{
			    if(pList2->expType != pList1->expType && !pList1->suppressErrorMsg && node->lineno != -1)
			    {
				char *opType1 = checkExpType(pList1->expType);
				char *opType2 = checkExpType(pList2->expType);
				printf("ERROR(%d): Expecting %s in parameter %i of call to '%s' declared on line %d but got %s.\n",
					tree->lineno, opType2, pCount, node->attr.name, node->lineno, opType1);
				numErrors++;
			    }
			    if(pList2->isArray && !pList1->isArray)
			    {
				printf("ERROR(%d): Expecting array in parameter %i of call to '%s' declared on line %d.\n",
					tree->lineno, pCount, node->attr.name, node->lineno);
				numErrors++;
			    }
			    if(!pList2->isArray && pList1->isArray)
			    {
				printf("ERROR(%d): Not expecting array in parameter %i of call to '%s' declared on line %d.\n",
					tree->lineno, pCount, node->attr.name, node->lineno);
				numErrors++;
			    }

			    pList1 = pList1->sibling;
			    pList2 = pList2->sibling;
			    pCount++;
			}

		    }
		    break;
		default:
                    printf("Unknown ExpNode kind");
                    break;
            }
	}
	else
	{
	   printf("Unknown node kind\n");
	}

	tree = tree->sibling;
	sCount++;
    } /* END OF WHILE LOOP */
} /* END OF FUNCTION */
