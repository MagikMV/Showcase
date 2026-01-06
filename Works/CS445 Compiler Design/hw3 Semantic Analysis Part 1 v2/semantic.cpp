/* semantic.cpp
 *
 * Miguel Villanueva
 * March 27, 2021
 */

#include "semantic.h"
using namespace std;

extern int numErrors;
int numWarnings;

void checkIfUsed(std::string s, void *ptr)
{
    TreeNode *node;
    node = (TreeNode *) ptr;
    if(!node->used)
    {
	printf("WARNING(%d): The variable \'%s\' seems not to be used.\n", node->lineno, node->attr.name);
        numWarnings++;
    }
}

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


void semanticAnalysis(TreeNode *syntaxTree, SymbolTable *symbolTable)
{
    traverseTree(syntaxTree, symbolTable);

    TreeNode *node = (TreeNode *) symbolTable->lookup("main");
    if(node == NULL)
    {
	printf("ERROR(LINKER): A function named 'main()' must be defined.\n");
	numErrors++;
    }
    else if(node->subkind.decl == VarK)
    {
	printf("ERROR(LINKER): A function named 'main()' must be defined.\n");
        numErrors++;
    }
    else
    {
	if(node->child[0] != NULL)
	{
	    printf("ERROR(LINKER): A function named 'main()' must be defined.\n");
	    numErrors++;
	}
    }
} /* END OF FUNCTION */

void traverseTree(TreeNode *tree, SymbolTable *table)
{
    int i;			// For children
    int sCount = 1;		// Sibling count
    TreeNode *node;		// Used for storing return from lookup
    char *expLHS;
    char *expRHS;

    while(tree != NULL)
    {
	if(tree->nodekind == DeclK)
	{
	    switch(tree->subkind.decl)
	    {
		case VarK:
		    //table->insert(tree->attr.name, tree);
		    if(!table->insert(tree->attr.name, tree))
		    {
			node = (TreeNode *) table->lookup(tree->attr.name);
			printf("ERROR(%d): Symbol '%s' is already declared at line %d.\n", tree->lineno, tree->attr.name, node->lineno);
			numErrors++;
		    }

		    //  Initialize variables with ':'
		    if(tree->child[0] != NULL && tree->child[0]->subkind.exp == IdK)
		    {
			node = (TreeNode *) table->lookup(tree->child[0]->attr.name);
			node->initialized = true;
		    }
		    else if(tree->child[0] != NULL && tree->child[0]->subkind.exp == ConstantK)
			tree->initialized = true;
		    else if(tree->child[0] != NULL && tree->child[0]->subkind.exp == OpK)
			tree->initialized = true;
		    
		    //  Initialize globals
		    if(table->depth() == 1)
			tree->initialized = true;

		    //  Traverse
                    traverseTree(tree->child[0], table);
                    traverseTree(tree->child[1], table);
                    traverseTree(tree->child[2], table);
		    break;
		case FuncK:
		    //table->insert(tree->attr.name, tree);
		    if(!table->insert(tree->attr.name, tree))
                    {
			node = (TreeNode *) table->lookup(tree->attr.name);
                        printf("ERROR(%d): Symbol '%s' is already declared at line %d.\n", tree->lineno, tree->attr.name, node->lineno);
                        numErrors++;
                    }

		    table->enter("Function");
		    if(tree->child[1] != NULL && tree->child[1]->subkind.stmt == CompoundK)
			tree->child[1]->compoundFlag = true;
		    
		    //  Traverse
		    traverseTree(tree->child[0], table);
		    traverseTree(tree->child[1], table);
		    traverseTree(tree->child[2], table);

		    //  Check if used and leave
                    table->applyToAll(checkIfUsed);
		    table->leave();
		    break;
		case ParamK:
		    //table->insert(tree->attr.name, tree);
		    if(!table->insert(tree->attr.name, tree))
                    {
			node = (TreeNode *) table->lookup(tree->attr.name);
                        printf("ERROR(%d): Symbol '%s' is already declared at line %d.\n", tree->lineno, tree->attr.name, node->lineno);
                        numErrors++;
                    }
		    tree->initialized = true;

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
                    traverseTree(tree->child[1], table);
                    traverseTree(tree->child[2], table);
		    break;
		case WhileK:
		    //  Traverse
                    traverseTree(tree->child[0], table);
                    traverseTree(tree->child[1], table);
                    traverseTree(tree->child[2], table);
		    break;
		case ForK:
		    tree->child[0]->initialized = true;  // Maybe used only for assignment 3
		    table->enter("For");
		    if(tree->child[2] != NULL && tree->child[2]->subkind.stmt == CompoundK)
			tree->child[2]->compoundFlag = true;

		    //  Traverse
                    traverseTree(tree->child[0], table);
                    traverseTree(tree->child[1], table);
                    traverseTree(tree->child[2], table);

		    //  Check if used and leave
		    table->applyToAll(checkIfUsed);
		    table->leave();
		    break;
		case CompoundK:
		    if(!tree->compoundFlag)
			table->enter("Compound");

		    //  Traverse
		    traverseTree(tree->child[0], table);
                    traverseTree(tree->child[1], table);
                    traverseTree(tree->child[2], table);

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
		    //  Traverse
                    traverseTree(tree->child[0], table);
                    traverseTree(tree->child[1], table);
                    traverseTree(tree->child[2], table);

		    //  Errors
		    if(tree->child[0] != NULL && tree->child[0]->subkind.exp == IdK)
		    {
			node = (TreeNode *) table->lookup(tree->child[0]->attr.name);
			if(node != NULL && node->isArray)
			{
			    printf("ERROR(%d): Cannot return an array.\n", tree->lineno);
			    numErrors++;
			}
		    }
		    break;
		case BreakK:
		    //  Traverse
                    traverseTree(tree->child[0], table);
                    traverseTree(tree->child[1], table);
                    traverseTree(tree->child[2], table);
		    break;
		case RangeK:
		    /*  For assignment 3, range does not get traversed 
		    //  Traverse
                    traverseTree(tree->child[0], table);
                    traverseTree(tree->child[1], table);
                    traverseTree(tree->child[2], table);*/
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
			    if(tree->child[1]->expType != Integer)
			    {
				expRHS = checkExpType(tree->child[1]->expType);
				printf("ERROR(%d): Array \'%s\' should be indexed by type int but got %s.\n", tree->lineno, tree->child[0]->attr.name, expRHS);
				numErrors++;
			    }
			}
			if(tree->child[1]->subkind.exp == IdK)  // If !IdK then tree->child[1] would be '['
			{
			    node = (TreeNode *) table->lookup(tree->child[1]->attr.name);
			    if(node != NULL && node->isArray)
			    {
				printf("ERROR(%d): Array index is the unindexed array \'%s\'.\n", tree->lineno, tree->child[1]->attr.name);
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
			if(tree->child[0]->subkind.exp == IdK)  // LHS
			{
			    node = (TreeNode *) table->lookup(tree->child[0]->attr.name);
			    //if(node == NULL || node->subkind.decl == FuncK)
				//break;
			    if(node != NULL && node->isArray)
			    {
				printf("ERROR(%d): The operation \'%s\' does not work with arrays.\n", tree->lineno, op);
				numErrors++;
			    }
			    if(tree->child[1]->subkind.exp == IdK && node != NULL && !node->isArray)
			    //if(tree->child[1]->subkind.exp == IdK)  // RHS
                            {
                        	node = (TreeNode *) table->lookup(tree->child[1]->attr.name);
                        	//if(node == NULL || node->subkind.decl == FuncK)
                            	    //break;
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
			}
			else if(tree->attr.op == 275)		// NOT
			{
			    op = (char *) "not";

			    if(tree->child[0]->suppressErrorMsg)  // If id is undeclared
                                break;

			    if(tree->child[0]->expType != Boolean)
			    {
				expRHS = checkExpType(tree->child[0]->expType);
				if(tree->child[0]->subkind.exp == ConstantK)
				{
				    printf("ERROR(%d): Unary \'%s\' requires an operand of %s but was given %s.\n", tree->lineno, op, opType, expRHS);
				    numErrors++;
				}
				else if(table->lookup(tree->child[0]->attr.name))
				{
                                    printf("ERROR(%d): Unary \'%s\' requires an operand of %s but was given %s.\n", tree->lineno, op, opType, expRHS);
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
				op = tree->attr.name;

			    if(tree->child[0]->expType != Integer)
                            {
                                expRHS = checkExpType(tree->child[0]->expType);
				if(tree->child[0]->subkind.exp == ConstantK)
				{
				    printf("ERROR(%d): Unary \'%s\' requires an operand of %s but was given %s.\n", tree->lineno, op, opType, expRHS);
				    numErrors++;
				}
				else if(table->lookup(tree->child[0]->attr.name))
				{
                                    printf("ERROR(%d): Unary \'%s\' requires an operand of %s but was given %s.\n", tree->lineno, op, opType, expRHS);
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
			    char *op = tree->attr.name;
			    expLHS = checkExpType(tree->child[0]->expType);
			    expRHS = checkExpType(tree->child[1]->expType);
			    printf("ERROR(%d): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n", tree->lineno, op, expLHS, expRHS); 
			    numErrors++;
			}
			if(tree->child[0]->subkind.exp == IdK)
                        {
                            node = (TreeNode *) table->lookup(tree->child[0]->attr.name);
                            if(node == NULL || node->subkind.decl == FuncK)
                                break;
			    else if(node != NULL && node->isArray)
			    {
				if(!tree->child[1]->isArray)
				{
				    if(tree->child[1]->subkind.exp == IdK)
				    {
					node = (TreeNode *) table->lookup(tree->child[1]->attr.name);
					if(node == NULL || !node->isArray)
					{
					    printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n", tree->lineno, tree->attr.name);
					    numErrors++;
					}
				    }
				    else
				    {
					printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n", tree->lineno, tree->attr.name);
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
					printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n", tree->lineno, tree->attr.name);
					numErrors++;
				    }
				}
			    }
			}
		    } /* END OF EQUAL TYPES CASE */
		    break;
		case ConstantK:
		    break;
		case IdK:
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
			tree->suppressErrorMsg = true;
                        printf("ERROR(%d): Cannot use function '%s' as a variable.\n", tree->lineno, node->attr.name);
                        numErrors++;
                    }
		    //  Warnings and types
                    //if(node != NULL)
		    else
		    {
                        tree->expType = node->expType;
			node->used = true;
			if(tree->initialized)
			    node->initialized = true;

			// Weird thing here
			if(node->isStatic)
			    node->initialized = true;

			if(!node->initialized && !node->iChecked)
			{
			    node->iChecked = true;
			    printf("WARNING(%d): Variable \'%s\' may be uninitialized when used here.\n", tree->lineno, tree->attr.name);
			    numWarnings++;
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
		    }

		    //  Traverse
                    traverseTree(tree->child[0], table);
                    traverseTree(tree->child[1], table);
                    traverseTree(tree->child[2], table);

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

			    expLHS = checkExpType(tree->child[0]->expType);
			    expRHS = checkExpType(tree->child[1]->expType);
			    printf("ERROR(%d): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n", tree->lineno, tree->attr.name, expLHS, expRHS);
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
					printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n", tree->lineno, tree->attr.name);
					numErrors++;
				    }
				}
				else if(!tree->child[1]->isArray)  // If rhs is not string
				{
				    printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n", tree->lineno, tree->attr.name);
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
                                        printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n", tree->lineno, tree->attr.name);
                                        numErrors++;
                                    }
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
				    printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n", tree->lineno, tree->attr.name);
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
			        printf("ERROR(%d): Unary \'%s\' requires an operand of %s but was given %s.\n", tree->lineno, op, opType, expLHS);
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
                            printf("ERROR(%d): \'%s\' requires operands of %s but lhs is of %s.\n", tree->lineno, op, opType, expLHS);
                            numErrors++;
                        }
                        if(!tree->child[1]->suppressErrorMsg && tree->child[1]->expType != tree->expType)
                        {
                            expRHS = checkExpType(tree->child[1]->expType);
                            printf("ERROR(%d): \'%s\' requires operands of %s but rhs is of %s.\n", tree->lineno, op, opType, expRHS);
                            numErrors++;
                        }
		    }
		    break;
		case InitK:
		    break;
		case CallK:
		    node = (TreeNode *) table->lookup(tree->attr.name);
                    if(node == NULL)
                    {
                        printf("ERROR(%d): Symbol '%s' is not declared.\n", tree->lineno, tree->attr.name);
                        numErrors++;
                    }
                    else if(node->subkind.decl != FuncK)
                    {
                        node->used = true;
                        printf("ERROR(%d): '%s' is a simple variable and cannot be called.\n", tree->lineno, tree->attr.name);
                        numErrors++;
                    }
                    else if(node != NULL)
                    {
                        tree->expType = node->expType;
                        node->used = true;
                    }

		    //  Traverse
                    traverseTree(tree->child[0], table);
                    traverseTree(tree->child[1], table);
                    traverseTree(tree->child[2], table);

		    /*node = (TreeNode *) table->lookup(tree->attr.name);
		    if(node == NULL)
		    {
			printf("ERROR(%d): Symbol '%s' is not declared.\n", tree->lineno, tree->attr.name);
			numErrors++;
		    }
		    else if(node->subkind.decl != FuncK)
		    {
			node->used = true;
			printf("ERROR(%d): '%s' is a simple variable and cannot be called.\n", tree->lineno, tree->attr.name);
			numErrors++;
		    }
		    else if(node != NULL)
                    {
                        tree->expType = node->expType;
                        node->used = true;
                    }*/
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
