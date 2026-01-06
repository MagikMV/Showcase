/* tree.cpp
 *
 * Miguel Villanueva
 * February 19, 2021
 */

#include "tree.h"

TreeNode *newDeclNode(DeclKind kind,
                      ExpType type,
                      TokenData *token,
                      TreeNode *c0,
                      TreeNode *c1,
                      TreeNode *c2)   // save TokenData block!!
{
TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));

    if(t == NULL)
    {
        printf("Out of memory error\n");
    }
    else
    {
        for(int i = 0; i < MAXCHILDREN; i++)
        {
            t->child[i] = NULL;
        }
        if(c0 != NULL)
        {
            t->child[0] = c0;
        }
        if(c1 != NULL)
        {
            t->child[1] = c1;
        }
        if(c2 != NULL)
        {
            t->child[2] = c2;
	}
        t->sibling = NULL;
	if(token != NULL)
	{
            t->lineno = token->linenum;
	    t->attr.name = token->tokenstr;
	}
        t->nodekind = DeclK;
        t->subkind.decl = kind;
	t->expType = type;
    }
    return t;
}

TreeNode *newStmtNode(StmtKind kind,
                      TokenData *token,
                      TreeNode *c0,
                      TreeNode *c1,
                      TreeNode *c2)
{
    TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));

    if(t == NULL)
    {
	printf("Out of memory error\n"); 
    }
    else
    {
	for(int i = 0; i < MAXCHILDREN; i++)
	{
	    t->child[i] = NULL;
	}
	if(c0 != NULL)
	{
	    t->child[0] = c0; 
	}
	if(c1 != NULL)
	{
	    t->child[1] = c1;
	}
	if(c2 != NULL)
	{
	    t->child[2] = c2;
	}
	t->sibling = NULL;
	t->lineno = token->linenum;
	t->nodekind = StmtK;
	t->subkind.stmt = kind;
    }
    return t;
}

TreeNode *newExpNode(ExpKind kind,
                     TokenData *token,
                     TreeNode *c0,
                     TreeNode *c1,
                     TreeNode *c2)
{
    TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));

    if(t == NULL)
    {
        printf("Out of memory error\n");
    }
    else
    {
        for(int i = 0; i < MAXCHILDREN; i++)
        {
            t->child[i] = NULL;
        }
	if(c0 != NULL)
        {
            t->child[0] = c0;
        }
        if(c1 != NULL)
        {
            t->child[1] = c1;
        }
        if(c2 != NULL)
        {
            t->child[2] = c2;
        }
        t->sibling = NULL;
        t->nodekind = ExpK;
        t->subkind.exp = kind;
	if(token != NULL)
        {
            t->lineno = token->linenum;
	    if(token->tokenclass == 261)           // NUMCONST
	    {
		t->expType = Integer;
		t->attr.value = token->nvalue;
	    }
	    else if(token->tokenclass == 269)	   // CHARCONST
	    {
		t->expType = Char;
		t->attr.cvalue = token->cvalue;
	    }
	    else if(token->tokenclass == 265)	   // STRINGCONST
	    {
		t->expType = Char;
		t->attr.string = token->svalue;
		//t->isArray = true;
	    }
	    else if(token->tokenclass == 276)	   // BOOLCONST
	    {
		t->expType = Boolean;
		t->attr.value = token->nvalue;
	    }

	    if(t->subkind.exp == OpK)
	    {
		if(token->tokenclass == 292)       // CHSIGN
                    t->attr.op = 292;
                else if(token->tokenclass == 293)  // SIZEOF
                    t->attr.op = 293;
		else if(token->tokenclass == 273)  // AND
		    t->attr.op = 273;
                else if(token->tokenclass == 274)  // OR
                    t->attr.op = 274;
                else if(token->tokenclass == 275)  // NOT
                    t->attr.op = 275;
		else
		    t->attr.string = token->tokenstr;
	    }
	    else if(t->subkind.exp == IdK)
	        t->attr.name = token->tokenstr;
	    else if(t->subkind.exp == AssignK)
	        t->attr.string = token->tokenstr;
	    else if(t->subkind.exp == CallK)
		t->attr.name = token->tokenstr;
        }
        //t->nodekind = ExpK;
        //t->subkind.exp = kind;
    }
    return t;
}

//  Add a TreeNode to a list of siblings.
//  Adding a NULL to the list is probably a programming error!
TreeNode *addSibling(TreeNode *t, TreeNode *s)
{
    if (s==NULL)
    {
        printf("ERROR(SYSTEM): never add a NULL to a sibling list.\n");
        exit(1);
    }
    if (t!=NULL)
    { 
        TreeNode *tmp;

        tmp = t;
        while(tmp->sibling!=NULL) 
	{
	    tmp = tmp->sibling;
	}
        tmp->sibling = s; 
        return t;
    }
    return s;
}

//  Pass the static and type attribute down the sibling list
void setType(TreeNode *t, ExpType type, bool isStatic)
{
    while(t)
    {
        t->expType = type;
        t->isStatic = isStatic;

        t = t->sibling;
    }
}

//  Variable indentno is used by printTree to
//  store current number of spaces to indent
//static int indentno = -1;
static int indentno = 0;

//  Macros to increase/decrease indentation
#define INDENT indentno+=1
#define UNINDENT indentno-=1

//  printSpaces indents by printing spaces
static void printSpaces()
{
    for (int i = 0; i < indentno; i++)
    {
        printf(".   ");
    }
}

void printTree(TreeNode *tree, bool typesFlag)
{
    int i;
    int sCount = 1;    // Sibling count
    INDENT;
    while(tree != NULL)
    {
	//printSpaces();
	if(tree->nodekind == DeclK)
	{
	    switch(tree->subkind.decl)
	    {
		case VarK:
		    if(tree->isArray != true)
		        printf("Var: %s of type ", tree->attr.name);
		    else
			printf("Var: %s is array of type ", tree->attr.name);

		    if(tree->expType == Integer)
			printf("int");
		    else if(tree->expType == Boolean)
			printf("bool");
		    else if(tree->expType == Char)
			printf("char");
		    break;
		case FuncK:
		    printf("Func: %s returns type", tree->attr.name);
		    if(tree->expType == Void)
			printf(" void");
		    if(tree->expType == Integer)
			printf(" int");
		    if(tree->expType == Boolean)
			printf(" bool");
		    if(tree->expType == Char)
			printf(" char");
		    break;
		case ParamK:
		    if(tree->isArray != true)
		        printf("Parm: %s of type", tree->attr.name);
		    else
			printf("Parm: %s is array of type", tree->attr.name);

                    if(tree->expType == Integer)
                        printf(" int");
                    if(tree->expType == Boolean)
                        printf(" bool");
                    if(tree->expType == Char)
                        printf(" char");
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
		    printf("NullK");
		    break;
		case IfK:
		    printf("If");
		    break;
		case WhileK:
		    printf("While");
		    break;
		case ForK:
		    printf("For");
		    break;
		case CompoundK:
		    printf("Compound");
		    break;
		case ReturnK:
		    printf("Return");
		    break;
		case BreakK:
		    printf("Break");
		    break;
		case RangeK:
		    printf("Range");
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
		    printf("Op: ");
		    if(tree->attr.op == 292)
		    {
			if(typesFlag)
			    printf("chsign");
			else
			    printf("CHSIGN");
		    }
		    else if(tree->attr.op == 293)
		    {
			if(typesFlag)
			    printf("sizeof");
			else
			    printf("SIZEOF");
		    }
		    else if(tree->attr.op == 273)
		    {
			if(typesFlag)
			    printf("and");
			else
			    printf("AND");
		    }
                    else if(tree->attr.op == 274)
		    {
			if(typesFlag)
			    printf("or");
			else
                            printf("OR");
		    }
		    else if(tree->attr.op == 275)
		    {
			if(typesFlag)
			    printf("not");
			else
			    printf("NOT");
		    }
		    else
			printf("%s", tree->attr.string);
		    if(typesFlag)
		    {
			printf(" of ");
                        if(tree->expType == Boolean)
			    printf("type bool");
			else if(tree->expType == Char)
			    printf("type char");
                        else if(tree->expType == Integer)
			    printf("type int");
			else if(tree->expType == UndefinedType)
			    printf("undefined type");
			else if(!tree->expType)                 // For assignment 3
                            printf("undefined type");
		    }
		    break;
		case ConstantK:
		    printf("Const ");
		    if(tree->isArray == true)
			printf("is array ");

		    if(typesFlag)			    // TYPES
		    {
			if(tree->expType == Integer)
			    printf("%d of type int", tree->attr.value);
			else if(tree->isArray == true)
			    printf("\"%s\" of type char", tree->attr.string);
			else if(tree->expType == Char)
			    printf("\'%c\' of type char", tree->attr.cvalue);
			else if(tree->expType == Boolean)
			{
                            if(tree->attr.value == 1)       // TRUE
                                printf("true of type bool");
                            else if(tree->attr.value == 0)  // FALSE
                                printf("false of type bool");
			}
		    }
		    else				    // NO TYPES
		    {
		        printf("of type ");
		        if(tree->expType == Integer)
			    printf("int: %d", tree->attr.value);
		        else if(tree->isArray == true)
			    printf("char: \"%s\"", tree->attr.string);
		        else if(tree->expType == Char)
			    printf("char: \'%c\'", tree->attr.cvalue);
		        else if(tree->expType == Boolean)
		        {
			    printf("bool: ");
			    if(tree->attr.value == 1)       // TRUE 
			        printf("true");
			    else if(tree->attr.value == 0)  // FALSE
			        printf("false");
		        }
		    }
		    break;
		case IdK:
		    printf("Id: %s", tree->attr.name);
		    if(typesFlag)
		    {
			//printf(" of type ");
			printf(" of ");
			if(tree->expType == Integer)
			    //printf("int");
			    printf("type int");
			else if(tree->expType == Char)
			    //printf("char");
			    printf("type char");
			else if(tree->expType == Boolean)
			    //printf("bool");
			    printf("type bool");
			else if(tree->expType == UndefinedType)
			    printf("undefined type");
			else if(!tree->expType)			// For assignment 3
			    printf("undefined type");
		    }
		    break;
		case AssignK:
		    printf("Assign: %s", tree->attr.string);
		    if(typesFlag)
		    {
			printf(" of type ");
			if(tree->expType == Integer)
			    printf("int");
			else if(tree->expType == Char)
			    printf("char");
			else if(tree->expType == Boolean)
			    printf("bool");
		    }
		    break;
		case InitK:
		    printf("InitK");
		    break;
		case CallK:
		    printf("Call: %s", tree->attr.name);
		    if(typesFlag)
		    {
			printf(" of type ");
			if(tree->expType == Void)
			    printf("void");
			else if(tree->expType == Integer)
			    printf("int");
			else if(tree->expType == Boolean)
			    printf("bool");
			else if(tree->expType == Char)
			    printf("char");
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
	printf(" [line: %d]\n", tree->lineno);
	for(i = 0; i < MAXCHILDREN; i++)
	{
            if(tree->child[i] != NULL)
            {
		printSpaces();
                printf("Child: %d  ", i);
            }
	    printTree(tree->child[i], typesFlag);
	}
	if(tree->sibling != NULL)
        {
            UNINDENT;
            printSpaces();
            printf("Sibling: %d  ", sCount);
            INDENT;
         }

	tree = tree->sibling;
	sCount++;
    } /* END OF WHILE LOOP */
    UNINDENT;
}
