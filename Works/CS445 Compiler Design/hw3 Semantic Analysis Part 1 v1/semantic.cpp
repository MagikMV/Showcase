/* semantic.cpp
 *
 * Miguel Villanueva
 * March 10, 2021
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
    SymbolTable *table = new SymbolTable();

    traverseTree(syntaxTree, table);
    typeCheck(syntaxTree, symbolTable);

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
}

void typeCheck(TreeNode *tree, SymbolTable *table)
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
					if(!table->insert(tree->attr.name, tree))
					{
						node = (TreeNode *) table->lookup(tree->attr.name);
						printf("ERROR(%d): Symbol '%s' is already declared at line %d.\n", tree->lineno, tree->attr.name, node->lineno);
						numErrors++;
					}		 
					if(tree->child[0] != NULL && tree->child[0]->subkind.exp == IdK)
					{
						node = (TreeNode *) table->lookup(tree->child[0]->attr.name);
						node->initialized = true;
					}
					else if(tree->child[0] != NULL && tree->child[0]->subkind.exp == ConstantK)
					{
						tree->initialized = true;
					}
					if(table->depth() == 1)
						tree->initialized = true;
					break;
				case FuncK:
					if(!table->insert(tree->attr.name, tree))
					{
						node = (TreeNode *) table->lookup(tree->attr.name);
							printf("ERROR(%d): Symbol '%s' is already declared at line %d.\n", tree->lineno, tree->attr.name, node->lineno);
							numErrors++;
					}
					table->enter("Function");
					tree->entered = true;
					if(tree->child[1] != NULL && tree->child[1]->subkind.stmt == CompoundK)
						tree->child[1]->compoundFlag = true;
					break;
				case ParamK:
					if(!table->insert(tree->attr.name, tree))
					{
						node = (TreeNode *) table->lookup(tree->attr.name);
						printf("ERROR(%d): Symbol '%s' is already declared at line %d.\n", tree->lineno, tree->attr.name, node->lineno);
						numErrors++;
					}
					tree->initialized = true;
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
					break;
				case WhileK:
					break;
				case ForK:
					tree->child[0]->initialized = true;
					table->enter("For");
					tree->entered = true;
					if(tree->child[2] != NULL && tree->child[2]->subkind.stmt == CompoundK)	
						tree->child[2]->compoundFlag = true;
					break;
				case CompoundK:
					if(tree->compoundFlag)
						tree->compoundFlag = false;
					else
					{
						table->enter("Compound");
						tree->entered = true;
					}
					break;
				case ReturnK:
					if(tree->child[0] != NULL && tree->child[0]->subkind.exp == IdK) //&& tree->child[0]->isArray)
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
					break;
				case RangeK:
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
					if(tree->undefinedRange)  // Only for Assignment 3 -_-
						break;

					if(tree->arrayOp && !tree->checkedInOp && !tree->alreadyPrinted)
					{
						//printf("made it here\n");
						if(tree->child[0]->subkind.exp == IdK)
						{
							node = (TreeNode *) table->lookup(tree->child[0]->attr.name);
							if(node == NULL)
							{
								printf("ERROR(%d): Symbol '%s' is not declared.\n", tree->child[0]->lineno, tree->child[0]->attr.name);
								numErrors++;
								tree->child[0]->checkedInArray = true;

								printf("ERROR(%d): Cannot index nonarray \'%s\'.\n", tree->child[0]->lineno, tree->child[0]->attr.name);
                        			numErrors++;
							}
							else if(node != NULL && !node->isArray)
							{
								printf("ERROR(%d): Cannot index nonarray \'%s\'.\n", tree->child[0]->lineno, tree->child[0]->attr.name);
								numErrors++;
							}
						}
						if(tree->child[1] != NULL && tree->child[1]->arrayOp)
						{
							// Helps cover.c- print in order
							if(tree->child[1]->child[0]->subkind.exp == IdK)
							{
								node = (TreeNode *) table->lookup(tree->child[1]->child[0]->attr.name);
								if(node == NULL)
								{
									printf("ERROR(%d): Symbol '%s' is not declared.\n", tree->child[1]->child[0]->lineno, tree->child[1]->child[0]->attr.name);
									numErrors++;
									tree->child[0]->checkedInArray = true;

									printf("ERROR(%d): Cannot index nonarray \'%s\'.\n", tree->child[1]->child[0]->lineno, tree->child[1]->child[0]->attr.name);
                        			numErrors++;
									tree->child[1]->alreadyPrinted = true;
								}
								else if(node != NULL && !node->isArray)
								{
									tree->child[1]->alreadyPrinted = true;
									printf("ERROR(%d): Cannot index nonarray \'%s\'.\n", tree->child[1]->child[0]->lineno, tree->child[1]->child[0]->attr.name);
									numErrors++;
								}
							}
							if(tree->child[1]->expType != Integer)
							{
								expRHS = checkExpType(tree->child[1]->expType);
								printf("ERROR(%d): Array \'%s\' should be indexed by type int but got %s.\n", tree->lineno, tree->child[0]->attr.name, expRHS);
								numErrors++;
								/*tree->child[1]->printAfter = true;
								after = tree->child[0]->attr.name;*/
							}
						}
						if(tree->child[1]->subkind.exp == IdK)
						{
							node = (TreeNode *) table->lookup(tree->child[1]->attr.name);
							if(node != NULL && node->isArray)
							{
								printf("ERROR(%d): Array index is the unindexed array \'%s\'.\n", tree->lineno, tree->child[1]->attr.name);
								numErrors++;
							}
						}
					}	
					else if(tree->unary)
					{
						char *op;
						char *opType = checkExpType(tree->expType);
						if(tree->attr.op == 292)		// CHSIGN
						{
							op = (char *) "chsign";
							if(tree->child[0]->expType != Integer)
							{
								//op = (char *) "chsign";
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
							if(tree->child[0]->subkind.exp == IdK)
							{
								node = (TreeNode *) table->lookup(tree->child[0]->attr.name);
								if(node != NULL && node->isArray)
								{
									printf("ERROR(%d): The operation \'%s\' does not work with arrays.\n", tree->lineno, op);
									numErrors++;
								}
							}
						}
						else if(tree->attr.op == 293)		// SIZEOF
						{
							op = (char *) "sizeof";
							if(tree->child[0]->subkind.exp == IdK)
							{
								node = (TreeNode *) table->lookup(tree->child[0]->attr.name);
								if(node != NULL && !node->isArray)
								{
									//op = (char *) "sizeof";
									//expRHS = checkExpType(tree->child[0]->expType);
									printf("ERROR(%d): The operation \'%s\' only works with arrays.\n", tree->lineno, op);
									numErrors++;
								}
							}
						}
						else if(tree->attr.op == 275)		// NOT
						{
							op = (char *) "not";
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
						else								// QUESTION MARK
						{
							op = tree->attr.name;
							if(tree->child[0]->expType != Integer)
							{
								//op = tree->attr.name;
								expRHS = checkExpType(tree->child[0]->expType);
								if(table->lookup(tree->child[0]->attr.name))
								{
									printf("ERROR(%d): Unary \'%s\' requires an operand of %s but was given %s.\n", tree->lineno, op, opType, expRHS);
									numErrors++;
								}
							}
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
					}
					else if(tree->equalTypes)
					{
						//printf("made it here\n");
						if(tree->child[0]->expType != tree->child[1]->expType)
						{
							if(tree->child[0]->subkind.exp == IdK)
							{
								node = (TreeNode *) table->lookup(tree->child[0]->attr.name);
								if(node == NULL || node->subkind.decl == FuncK)
									break;
                    		}
							// Lookup added for ID because of the traversal used
							if(tree->child[0]->subkind.exp == IdK)
							{
								if(!node->initialized && !node->iChecked)
								{
									node->iChecked = true;
									printf("WARNING(%d): Variable \'%s\' may be uninitialized when used here.\n", tree->child[0]->lineno, tree->child[0]->attr.name);
									numWarnings++;
								}
							}
							if(tree->child[1]->subkind.exp == IdK)
							{
								node = (TreeNode *) table->lookup(tree->child[1]->attr.name);
								if(node == NULL || node->subkind.decl == FuncK)
									break;
							}
							// Lookup added for ID because of the traversal used
							if(tree->child[1]->subkind.exp == IdK)
							{
								if(!node->initialized && !node->iChecked)
								{
									node->iChecked = true;
									printf("WARNING(%d): Variable \'%s\' may be uninitialized when used here.\n", tree->child[1]->lineno, tree->child[1]->attr.name); 
									numWarnings++;
								}
							}
							char *op = tree->attr.name;
							expLHS = checkExpType(tree->child[0]->expType);
							expRHS = checkExpType(tree->child[1]->expType);
							printf("ERROR(%d): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n", tree->lineno, op, expLHS, expRHS); 
							numErrors++;
						}
						if(tree->child[0]->subkind.exp == IdK)
						{
							//printf("made it here\n");
							node = (TreeNode *) table->lookup(tree->child[0]->attr.name);
							if(node == NULL || node->subkind.decl == FuncK)
								break;
							else if(node != NULL && node->isArray)
							{
								//if(tree->child[1]->subkind.exp == ConstantK)
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
			
						if(tree->child[0]->subkind.exp == OpK || tree->child[1]->subkind.exp == OpK)
						{
							if(tree->child[0]->arrayOp)
							{
								node = (TreeNode *) table->lookup(tree->child[0]->child[0]->attr.name);
								if(node == NULL)
								{
									printf("ERROR(%d): Symbol '%s' is not declared.\n", tree->child[0]->child[0]->lineno, tree->child[0]->child[0]->attr.name);
									numErrors++;
									tree->child[0]->child[0]->checkedInArray = true;
									tree->child[0]->checkedInOp = true;
									printf("ERROR(%d): Cannot index nonarray \'%s\'.\n", tree->child[0]->child[0]->lineno, tree->child[0]->child[0]->attr.name);
                        			numErrors++;
			    				}
			    				else if(!node->isArray)
			    				{
									tree->child[0]->checkedInOp = true;
									printf("ERROR(%d): Cannot index nonarray \'%s\'.\n", tree->child[0]->child[0]->lineno, tree->child[0]->child[0]->attr.name);
									numErrors++;
			    				}
							}
							if(tree->child[1]->arrayOp)
							{
								node = (TreeNode *) table->lookup(tree->child[1]->child[0]->attr.name);
								if(node == NULL)
								{
									printf("ERROR(%d): Symbol '%s' is not declared.\n", tree->child[1]->child[0]->lineno, tree->child[1]->child[0]->attr.name);
									numErrors++;
									tree->child[1]->child[0]->checkedInArray = true;
									tree->child[1]->checkedInOp = true;
									printf("ERROR(%d): Cannot index nonarray \'%s\'.\n", tree->child[1]->child[0]->lineno, tree->child[1]->child[0]->attr.name);
									numErrors++;
								}
								else if(!node->isArray)
								{
									tree->child[1]->checkedInOp = true;
									printf("ERROR(%d): Cannot index nonarray \'%s\'.\n", tree->child[1]->child[0]->lineno, tree->child[1]->child[0]->attr.name);
									numErrors++;
								}
							}
							if(tree->child[0]->arrayOp)  // SECOND PASS
							{
								if(tree->child[0]->child[1] != NULL && tree->child[1]->subkind.exp == OpK)
								{
									if(tree->child[0]->child[1]->expType != Integer)
									{
										tree->child[0]->child[0]->checkedInOp = true;
										expRHS = checkExpType(tree->child[0]->child[1]->expType);
										printf("ERROR(%d): Array \'%s\' should be indexed by type int but got %s.\n", tree->child[0]->lineno, tree->child[0]->child[0]->attr.name);
										numErrors++;
									}
								}
							}
							if(tree->child[1]->arrayOp)  // SECOND PASS
							{
								if(tree->child[1]->child[1] != NULL && tree->child[1]->subkind.exp == OpK)
								{
									if(tree->child[1]->child[1]->expType != Integer)
									{
										tree->child[1]->child[0]->checkedInOp = true;
										expRHS = checkExpType(tree->child[1]->child[1]->expType);
										printf("ERROR(%d): Array \'%s\' should be indexed by type int but got %s.\n", tree->child[1]->lineno, tree->child[1]->child[0]->attr.name);
										numErrors++;
									}
								}
							}
							if(tree->child[0]->expType != tree->expType)
							{
                        		expLHS = checkExpType(tree->child[0]->expType);
                        		printf("ERROR(%d): \'%s\' requires operands of %s but lhs is of %s.\n", tree->lineno, op, opType, expLHS);
                       			numErrors++;
							}
							if(tree->child[1]->expType != tree->expType)
							{
								expRHS = checkExpType(tree->child[1]->expType);
								printf("ERROR(%d): \'%s\' requires operands of %s but rhs is of %s.\n", tree->lineno, op, opType, expRHS);
								numErrors++;
							}
							break;
						}
						if(tree->child[0]->subkind.exp == IdK)
						{
							node = (TreeNode *) table->lookup(tree->child[0]->attr.name);
							if(node == NULL || node->subkind.decl == FuncK)
								break;
							else if(node->isArray)
							{
								printf("ERROR(%d): The operation \'%s\' does not work with arrays.\n", tree->lineno, op);
								numErrors++;
							}
							if(tree->child[1]->subkind.exp == IdK && !node->isArray)
							{
								node = (TreeNode *) table->lookup(tree->child[1]->attr.name);
								if(node == NULL || node->subkind.decl == FuncK)
									break;
								else if(node->isArray)
								{
									printf("ERROR(%d): The operation \'%s\' does not work with arrays.\n", tree->lineno, op);
									numErrors++;
								}
							}
						}
						if(tree->child[0]->expType != tree->expType)
						{
							// Lookup added for ID because of scope.out and the traversal used
							if(tree->child[0]->subkind.exp == IdK)
							{
								if(!node->initialized && !node->iChecked)
								{
                        			node->iChecked = true;
                        			printf("WARNING(%d): Variable \'%s\' may be uninitialized when used here.\n", tree->child[0]->lineno, tree->child[0]->attr.name);
                        			numWarnings++;
								}
							}
							expLHS = checkExpType(tree->child[0]->expType);
							printf("ERROR(%d): \'%s\' requires operands of %s but lhs is of %s.\n", tree->lineno, op, opType, expLHS);
							numErrors++;
						}
						if(tree->child[1]->expType != tree->expType)
						{
							expRHS = checkExpType(tree->child[1]->expType);
							printf("ERROR(%d): \'%s\' requires operands of %s but rhs is of %s.\n", tree->lineno, op, opType, expRHS);
							numErrors++;
						}
					}
					break;
				case ConstantK:
					break;
				case IdK:
					if(tree->checkedInArray)
						break;
					if(tree->undefinedRange)  // Temporary for Assignment 3
						break;
					node = (TreeNode *) table->lookup(tree->attr.name);
					if(node == NULL)
					{
						printf("ERROR(%d): Symbol '%s' is not declared.\n", tree->lineno, tree->attr.name);
						numErrors++;
					}
					else if(node->subkind.decl == FuncK)
					{
						printf("ERROR(%d): Cannot use function '%s' as a variable.\n", tree->lineno, node->attr.name);
						numErrors++;
					}
					else
					{
						// Weird thing here
						if(node->isStatic)
							node->initialized = true;

						if(tree->seenOnLHS)
						{
							node->initialized = true;
							//printf("Activated initialized off seenOnLHS\n");
						}		

						if(!node->initialized && !node->iChecked)
						{
							node->iChecked = true;
							printf("WARNING(%d): Variable \'%s\' may be uninitialized when used here.\n", tree->lineno, tree->attr.name);
							numWarnings++;
						}
						else if(node->sameCheck && !node->iChecked)
						{
							node->iChecked = true;
							printf("WARNING(%d): Variable \'%s\' may be uninitialized when used here.\n", tree->lineno, tree->attr.name);
							numWarnings++;
						}
					}
					break;
				case AssignK:
					//printf("I got here\n");
					if(tree->equalSign)
					{
						//printf("I made it inside\n");
						if(tree->child[0]->subkind.exp == OpK)  // LHS is array
						{
							node = tree->child[0];
							node = (TreeNode *) table->lookup(node->child[0]->attr.name);
							if(node != NULL)
								node->initialized = true;
							node = tree->child[0]; // Return from lookup back to array
							while(node->child[1] != NULL && node->child[1]->subkind.exp == OpK)  // CHANGED HERE
							{
								node = node->child[1];
								node->child[0]->seenOnLHS = true;
							}
							if(node->child[1] != NULL && node->child[1]->subkind.exp == IdK)  // CHANGED HERE
							{
								node = (TreeNode *) table->lookup(node->child[1]->attr.name);
								if(node != NULL)
									node->initialized = true;
							}
						}
						else
						{
							//printf("made it here\n");
							node = (TreeNode *) table->lookup(tree->child[0]->attr.name);  // LHS
							if(node != NULL && tree->child[1] != NULL && tree->child[1]->subkind.exp == IdK)
							{
								//printf("here\n");
								if(strcmp(tree->child[0]->attr.name, tree->child[1]->attr.name) == 0)
								{
									if(!node->initialized)
									node->sameCheck = true;
								}
								else
									node->initialized = true;
							}
							else if(node != NULL)
							{
								//printf("or here\n");
								if(tree->child[1]->subkind.exp == OpK)
								{
									if(tree->arrayOp)
									{
										//printf("here\n");
										node = (TreeNode *) table->lookup(tree->child[1]->child[0]->attr.name);
										//printf("but not here\n");
										if(node != NULL && !node->initialized)
										{
											node = (TreeNode *) table->lookup(tree->child[0]->attr.name);
											node->initialized = false;
										}
										else
										{
											node = (TreeNode *) table->lookup(tree->child[0]->attr.name);
											node->initialized = true;
										}
									}
								}
								else if(node != NULL)
								//else
									node->initialized = true;
							}
							//printf("was here\n");
							//if(node != NULL)
							//node->initialized = true;
							}
					}
					//printf("made it one the outside\n");
	
					if(tree->equalSign)
					{
						if(tree->child[0]->subkind.exp == IdK)
						{
							node = (TreeNode *) table->lookup(tree->child[0]->attr.name);
							if(node == NULL || node->subkind.decl == FuncK)
								break;
							else if(node != NULL && node->isArray)
							{
								//if(tree->child[1]->subkind.exp == ConstantK)
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
						else if(tree->child[0]->subkind.exp == OpK)
						{
							node = tree->child[0];
							node = (TreeNode *) table->lookup(tree->child[0]->attr.name);
							if(node == NULL)
								break;
							/*else
							{
							if(tree->child[1]->subkind.exp != OpK)
							{
								printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n", tree->lineno, tree->attr.name); 
							}
							}*/	
						}
						//else if child[1] == OpK
						if(tree->child[0]->expType != tree->child[1]->expType)
						{
							expLHS = checkExpType(tree->child[0]->expType);
							expRHS = checkExpType(tree->child[1]->expType);
							printf("ERROR(%d): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n", tree->lineno, tree->attr.name, expLHS, expRHS);
							numErrors++;
						}
					}
					else
					{	
						char *op = tree->attr.name;
						if(tree->expType != tree->child[0]->expType)
						{
							//char *op = tree->attr.name;
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
					break;
				default:
					//printf("Unknown ExpNode kind");
					break;
			}
		}
		else
		{
		   printf("Unknown node kind\n");
		}
		for(i = 0; i < MAXCHILDREN; i++)
			typeCheck(tree->child[i], table);

		if(tree->entered)
		{
			table->applyToAll(checkIfUsed);
			table->leave();
			//printf("Leaving scope\n");
		}

		tree = tree->sibling;
		sCount++;
    } /* END OF WHILE LOOP */
} /* END OF FUNCTION */

void traverseTree(TreeNode *tree, SymbolTable *table)
{
    int i;			// For children
    int sCount = 1;		// Sibling count
    TreeNode *node;		// Used for storing return from lookup
    while(tree != NULL)
    {
	if(tree->nodekind == DeclK)
	{
	    switch(tree->subkind.decl)
	    {
		case VarK:
		    table->insert(tree->attr.name, tree);
		    break;
		case FuncK:
		    table->insert(tree->attr.name, tree);
		    table->enter("Function");
		    tree->entered = true;
		    if(tree->child[1] != NULL && tree->child[1]->subkind.stmt == CompoundK)
			tree->child[1]->compoundFlag = true;
		    break;
		case ParamK:
                    table->insert(tree->attr.name, tree);
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
				break;
			case WhileK:
				break;
			case ForK:
				table->enter("For");
				tree->entered = true;
				if(tree->child[2] != NULL && tree->child[2]->subkind.stmt == CompoundK)
					tree->child[2]->compoundFlag = true;
				break;
			case CompoundK:
				if(tree->compoundFlag)
					tree->compoundFlag = false;
				else
				{
					table->enter("Compound");
					tree->entered = true;
					//printf("Entered new compound scope\n");
				}
				break;
			case ReturnK:
				break;
			case BreakK:
				break;
			case RangeK:
				if(tree->child[0] != NULL)
		    		tree->child[0]->undefinedRange = true;
				if(tree->child[1] != NULL)
					tree->child[1]->undefinedRange = true;
				if(tree->child[2] != NULL)
					tree->child[2]->undefinedRange = true;
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
					if(tree->undefinedRange)  // Temporary for Assignment 3
					{
						tree->expType = UndefinedType;
						if(tree->child[0] != NULL && tree->child[0]->subkind.exp == IdK)  // CHANGED
							tree->child[0]->undefinedRange = true;
						else if(tree->child[0] != NULL && tree->child[0]->subkind.exp == OpK)
							tree->child[0]->undefinedRange = true;

						if(tree->child[1] != NULL && tree->child[1]->subkind.exp == IdK)  // CHANGED
							tree->child[1]->undefinedRange = true;
						break;
					}
					if(tree->child[0] != NULL && tree->child[0]->subkind.exp == IdK)
					{
						node = (TreeNode *) table->lookup(tree->child[0]->attr.name);
						if(node != NULL)
						{
							if(node->expType == Boolean)
							tree->boolOp = true;
							else if(node->expType == Char)
							tree->charOp = true;
						}
					}
					if(tree->boolOp)
					{
						tree->expType = Boolean;
					}
					else if(tree->charOp)
					{
						tree->expType = Char;
					}
					else
					{
						tree->expType = Integer;
					}
					if(tree->attr.op == 292)	   // CHSIGN
						tree->expType = Integer;
					else if(tree->attr.op == 293)  // SIZEOF
						tree->expType = Integer;
					else if(tree->attr.op == 273)  // AND
						tree->expType = Boolean;
					else if(tree->attr.op == 274)  // OR
						tree->expType = Boolean;
					else if(tree->attr.op == 275)  // NOT
						tree->expType = Boolean;
					else if(tree->question)
						tree->expType = Integer;
					else if(tree->intInt)
					{
						tree->expType = Integer;
					}
					break;
				case ConstantK:
					break;
				case IdK:
					if(tree->undefinedRange)  // Temporary for Assignment 3
					{
						tree->expType = UndefinedType;
						break;
					}
					node = (TreeNode *) table->lookup(tree->attr.name);
					if(node != NULL)
					{
						tree->expType = node->expType;
						node->used = true;			
					}
					break;
				case AssignK:
					if(tree->equalSign)
					{
						if(tree->child[0]->subkind.exp == OpK)  // LHS is array
						{
							node = tree->child[0];
							node = (TreeNode *) table->lookup(node->child[0]->attr.name);
							if(node != NULL)
							{
								tree->expType = node->expType;
								node = tree->child[0]; // Return from lookup back to array
								if(tree->expType == Boolean)
									node->boolOp = true;
								else if(tree->expType == Char)
									node->charOp = true;
							}
						}
						else
						{
							node = (TreeNode *) table->lookup(tree->child[0]->attr.name);  // LHS
							if(node != NULL)
								tree->expType = node->expType;
						}
					}
					else
						tree->expType = Integer;
					break;
				case InitK:
					break;
				case CallK:
					node = (TreeNode *) table->lookup(tree->attr.name);
					if(node != NULL)
					tree->expType = node->expType;
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

	for(i = 0; i < MAXCHILDREN; i++)
	    traverseTree(tree->child[i], table);

	if(tree->entered)
	{
	    table->leave();
	}

	tree = tree->sibling;
	sCount++;
    } /* END OF WHILE LOOP */
} /* END OF FUNCTION */
