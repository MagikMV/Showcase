/* parser.y
 *
 * Miguel Villanueva
 * CS 445
 * May 9, 2021
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "scantype.h"
#include "ourGetopt.h"
#include "tree.h"
#include "symbolTable.h"
#include "semantic.h"
#include "ioTree.h"
#include "yyerror.h"
#include "emitcode.h"
#include "codegen.h"

extern int yylex();
extern FILE *yyin;
extern int line;
extern int numErrors;
extern int numWarnings;
extern int goffset;
FILE *code;

using namespace std;

#define YYERROR_VERBOSE

TreeNode *syntaxTree;
SymbolTable *symbolTable = new SymbolTable();
TreeNode *ioLibrary = ioTree();
%}

//// your %union statement
%union
{
    ExpType type;          // For passing types
    TokenData *tokenData;  // For terminals
    TreeNode *tree;        // For nonterminals
}
	/* Declarations */
//// your %token statements defining token classes
%token <tokenData> '%' '*' '(' ')' '-' '{' '}' '[' ']'
%token <tokenData> ':' ';' '<' '>' '?' ',' '/' '=' '+'
%token <tokenData> ADDASS ID INT NUMCONST IF EQ RETURN STRINGCONST THEN ELSE DEC CHARCONST
%token <tokenData> BOOL CHAR STATIC AND OR NOT BOOLCONST FOR TO BY DO BREAK WHILE
%token <tokenData> INC MIN MAX GEQ LEQ NEQ SUBASS MULASS DIVASS

%type <tree> program declList decl varDecl funDecl parms parmList parmTypeList
%type <tree> stmt matched unmatched simpleExp otherStmts iterRange expStmt compoundStmt
%type <tree> returnStmt breakStmt exp localDecls stmtList scopedVarDecl varDeclList
%type <tree> varDeclInit varDeclId parmIdList parmId mutable andExp unaryRelExp relExp
%type <tree> minmaxExp sumExp mulExp unaryExp factor
%type <tree> immutable call constant args argList

%type <type> typeSpec
%type <tokenData> relop minmaxop sumop mulop unaryop assignop
%token <tokenData> CHSIGN SIZEOF

%%

	/* Grammar */
program         : declList				   { syntaxTree = $1; }
		;

declList	: declList decl				   { if($2 != NULL) $$ = addSibling($1, $2); }
		| decl					   { $$ = $1; }
		;

decl		: varDecl				   { $$ = $1; }
		| funDecl				   { $$ = $1; }
		| error					   { $$ = NULL; }
		;

varDecl		: typeSpec varDeclList ';'		   { $$ = $2; setType($$, $1, false); yyerrok; }
		| error varDeclList ';'			   { $$ = NULL; yyerrok; }
		| typeSpec error ';'			   { $$ = NULL; yyerrok; }
		;

scopedVarDecl   : STATIC typeSpec varDeclList ';'	   { $$ = $3; setType($$, $2, true); yyerrok; }
		| typeSpec varDeclList ';'		   { $$ = $2; setType($$, $1, false); yyerrok; }
		;

varDeclList	: varDeclList ',' varDeclInit		   { if($3 != NULL) $$ = addSibling($1, $3); yyerrok; }
		| varDeclList ',' error			   { $$ = NULL; }
		| error					   { $$ = NULL; }
		| varDeclInit				   { $$ = $1; }
		;

varDeclInit	: varDeclId				   { $$ = $1; }
		| varDeclId ':' simpleExp		   { if($1 != NULL) $1->child[0] = $3; $$ = $1; }
		| error ':' simpleExp			   { $$ = NULL; yyerrok; }
		;

varDeclId	: ID					   { $$ = newDeclNode(VarK, UndefinedType, $1); $$->size = 1; }
		| ID '[' NUMCONST ']'			   { $$ = newDeclNode(VarK, UndefinedType, $1); $$->isArray = true; $$->size = $3->nvalue + 1; }
		| ID '[' error				   { $$ = NULL; }
		| error ']'				   { $$ = NULL; yyerrok; }
		;

typeSpec	: INT					   { $$ = Integer; }
		| BOOL					   { $$ = Boolean; }
		| CHAR					   { $$ = Char; }
		;

funDecl		: typeSpec ID '(' parms ')' stmt	   { $$ = newDeclNode(FuncK, $1, $2, $4, $6); }
		| typeSpec error			   { $$ = NULL; }
		| typeSpec ID '(' error			   { $$ = NULL; }
		| ID '(' parms ')' stmt			   { $$ = newDeclNode(FuncK, Void, $1, $3, $5); }
		| ID '(' error				   { $$ = NULL; }
		| ID '(' parms ')' error		   { $$ = NULL; }
		;

parms		: parmList				   { $$ = $1; }
		| /* Epsilon */				   { $$ = NULL; }
		;

parmList	: parmList ';' parmTypeList		   { if($3 != NULL) $$ = addSibling($1, $3); }
		| parmList ';' error			   { $$ = NULL; }
		| error					   { $$ = NULL; }
		| parmTypeList				   { $$ = $1; }
		;

parmTypeList	: typeSpec parmIdList			   { $$ = $2; setType($$, $1, false); }
		| typeSpec error			   { $$ = NULL; }
		;

parmIdList	: parmIdList ',' parmId			   { if($3 != NULL) $$ = addSibling($1, $3); yyerrok; }
		| parmIdList ',' error			   { $$ = NULL; }
		| error					   { $$ = NULL; }
		| parmId				   { $$ = $1; }
		;

parmId		: ID					   { $$ = newDeclNode(ParamK, UndefinedType, $1); }
		| ID '[' ']'				   { $$ = newDeclNode(ParamK, UndefinedType, $1); $$->isArray = true; }
		;

stmt		: matched				   { $$ = $1; }
		| unmatched				   { $$ = $1; }
		;

matched         : IF simpleExp THEN matched ELSE matched   { $$ = newStmtNode(IfK, $1, $2, $4, $6); }
		| IF error				   { $$ = NULL; }
		| IF error ELSE matched			   { $$ = NULL; yyerrok; }
		| IF error THEN matched ELSE matched	   { $$ = NULL; yyerrok; }
		| WHILE simpleExp DO matched		   { $$ = newStmtNode(WhileK, $1, $2, $4); }
		| WHILE error DO matched		   { $$ = NULL; yyerrok; }
		| WHILE error				   { $$ = NULL; }
		| FOR ID '=' iterRange DO matched	   { $$ = newStmtNode(ForK, $1, newDeclNode(VarK, Integer, $2), $4, $6); }
		| FOR ID '=' error DO matched		   { $$ = NULL; yyerrok; }
		| FOR error				   { $$ = NULL; }
		| otherStmts				   { $$ = $1; }
                ;

unmatched	: IF simpleExp THEN matched		   { $$ = newStmtNode(IfK, $1, $2, $4); }
		| IF simpleExp THEN unmatched		   { $$ = newStmtNode(IfK, $1, $2, $4); }
		| IF simpleExp THEN matched ELSE unmatched { $$ = newStmtNode(IfK, $1, $2, $4, $6); }
		| IF error THEN stmt			   { $$ = NULL; yyerrok; }
		| IF error THEN matched ELSE unmatched	   { $$ = NULL; yyerrok; }
		| WHILE simpleExp DO unmatched		   { $$ = newStmtNode(WhileK, $1, $2, $4); }
		| FOR ID '=' iterRange DO unmatched 	   { $$ = newStmtNode(ForK, $1, newDeclNode(VarK, Integer, $2), $4, $6); }
		;

otherStmts	: expStmt				   { $$ = $1; }
		| compoundStmt			   	   { $$ = $1; }
		| returnStmt				   { $$ = $1; }
		| breakStmt				   { $$ = $1; }
		;
	   
expStmt		: exp ';'				   { $$ = $1; }
		| error ';'				   { $$ = NULL; yyerrok; }
		| ';'					   { $$ = NULL; }
		;

compoundStmt	: '{' localDecls stmtList '}'		   { $$ = newStmtNode(CompoundK, $1, $2, $3); yyerrok; }
		;

localDecls	: localDecls scopedVarDecl		   { if($2 != NULL) $$ = addSibling($1, $2); }
		| /* Epsilon */				   { $$ = NULL; }
		;

stmtList	: stmtList stmt				   { if($2 != NULL) $$ = addSibling($1, $2); }
		| /* Epsilon */				   { $$ = NULL; }
		;

iterRange	: simpleExp TO simpleExp		   { $$ = newStmtNode(RangeK, $2, $1, $3); }
		/*| simpleExp TO error			   { $$ = NULL; }*/
		| simpleExp TO simpleExp BY simpleExp	   { $$ = newStmtNode(RangeK, $2, $1, $3, $5); }
		| simpleExp TO error                       { $$ = NULL; }
		| error BY error			   { $$ = NULL; yyerrok; }
		| simpleExp TO simpleExp BY error	   { $$ = NULL; }
		;

returnStmt	: RETURN ';'				   { $$ = newStmtNode(ReturnK, $1); }
		| RETURN exp ';'			   { $$ = newStmtNode(ReturnK, $1, $2); yyerrok; }
		| RETURN error ';'			   { $$ = NULL; yyerrok; }
		;

breakStmt	: BREAK ';'				   { $$ = newStmtNode(BreakK, $1); }
		;

exp		: mutable assignop exp			   { $$ = newExpNode(AssignK, $2, $1, $3); }
		| error assignop exp			   { $$ = NULL; yyerrok; }
		| mutable assignop error		   { $$ = NULL; }
		| mutable INC				   { $$ = newExpNode(AssignK, $2, $1); $$->unary = true; }
		| mutable DEC				   { $$ = newExpNode(AssignK, $2, $1); $$->unary = true; }
		| error INC				   { $$ = NULL; yyerrok; }
		| error DEC				   { $$ = NULL; yyerrok; }
		| simpleExp				   { $$ = $1; }
		;

assignop	: '='					   { $$ = $1; }
		| ADDASS				   { $$ = $1; }
		| SUBASS				   { $$ = $1; }
		| MULASS				   { $$ = $1; }
		| DIVASS				   { $$ = $1; }
		

simpleExp	: simpleExp OR andExp			   { $$ = newExpNode(OpK, $2, $1, $3); $$->boolOp = true; $$->boolbool = true; }
		| simpleExp OR error			   { $$ = NULL; }
		| andExp				   { $$ = $1; }
		;

andExp		: andExp AND unaryRelExp		   { $$ = newExpNode(OpK, $2, $1, $3); $$->boolOp = true; $$->boolbool = true; }
		| andExp AND error			   { $$ = NULL; }
		| unaryRelExp				   { $$ = $1; }
		;

unaryRelExp	: NOT unaryRelExp			   { $$ = newExpNode(OpK, $1, $2); $$->boolOp = true; $$->unary = true; }
		| NOT error				   { $$ = NULL; }
		| relExp				   { $$ = $1; }
		;

relExp		: minmaxExp relop minmaxExp		   { $$ = newExpNode(OpK, $2, $1, $3); $$->boolOp = true; $$->equalTypes = true; }
		| minmaxExp relop error			   { $$ = NULL; }
		| minmaxExp				   { $$ = $1; }
		;

relop		: LEQ					   { $$ = $1; }
		| '<'					   { $$ = $1; }
		| '>'					   { $$ = $1; }
		| GEQ					   { $$ = $1; }
		| EQ					   { $$ = $1; }
		| NEQ					   { $$ = $1; }
		;

minmaxExp	: minmaxExp minmaxop sumExp		   { $$ = newExpNode(OpK, $2, $1, $3); $$->intInt = true; }
		| sumExp				   { $$ = $1; }
		;

minmaxop	: MAX					   { $$ = $1; }
		| MIN					   { $$ = $1; }
		;

sumExp		: sumExp sumop mulExp			   { $$ = newExpNode(OpK, $2, $1, $3); $$->intInt = true; }
		| sumExp sumop error			   { $$ = NULL; }
		| mulExp				   { $$ = $1; }
		;

sumop		: '+'					   { $$ = $1; }
		| '-'					   { $$ = $1; }
		;

mulExp		: mulExp mulop unaryExp			   { $$ = newExpNode(OpK, $2, $1, $3); $$->intInt = true; }
		| mulExp mulop error			   { $$ = NULL; }
		| unaryExp				   { $$ = $1; }
		;

mulop		: '*'					   { $$ = $1; }
		| '/'					   { $$ = $1; }
		| '%'					   { $$ = $1; }
		;

unaryExp	: unaryop unaryExp			   { $$ = newExpNode(OpK, $1, $2); $$->unary = true; }
		| unaryop error				   { $$ = NULL; }
		| factor				   { $$ = $1; }
		;

unaryop		: '-'					   { $1->tokenclass = CHSIGN; $$ = $1; }
		| '*'					   { $1->tokenclass = SIZEOF; $$ = $1; }
		| '?'					   { $$ = $1; }
		;

factor		: immutable				   { $$ = $1; }
		| mutable				   { $$ = $1; }
		;

mutable		: ID					   { $$ = newExpNode(IdK, $1); }
		| ID '[' exp ']'			   { $$ = newExpNode(OpK, $2, newExpNode(IdK, $1), $3); $$->arrayOp = true; }
		;

immutable	: '(' exp ')'				   { $$ = $2; yyerrok; }
		| '(' error				   { $$ = NULL; }
		| call					   { $$ = $1; }
		| constant				   { $$ = $1; }
		;

call		: ID '(' args ')'			   { $$ = newExpNode(CallK, $1, $3); }
		| error '('				   { $$ = NULL; yyerrok; }
		;

args		: argList				   { $$ = $1; }
		| /* Epsilon */				   { $$ = NULL; }
		;

argList		: argList ',' exp			   { if($3 != NULL) $$ = addSibling($1, $3); yyerrok; }
		| argList ',' error			   { $$ = NULL; }
		| exp					   { $$ = $1; }
		;

constant	: NUMCONST				   { $$ = newExpNode(ConstantK, $1); }
		| CHARCONST				   { $$ = newExpNode(ConstantK, $1); }
		| STRINGCONST				   { $$ = newExpNode(ConstantK, $1); $$->isArray = true; }
		| BOOLCONST				   { $$ = newExpNode(ConstantK, $1); }
		;

%%

	/* Subroutines */
//// any functions for main here

int main(int argc, char *argv[])
{
    int c;
    extern char *optarg;
    extern int optind;
    int printTreeFlag;      // -p
    int treePlusTypeFlag;   // -P
    int usageFlag;	    // -h
    extern int yydebug;     // -d   Moved from definitions section
    int memFlag;	    // -M
    int errflg;
    char *ofile;
    const char *filename;

    printTreeFlag = 0;
    treePlusTypeFlag = 0;
    memFlag = 0;
    usageFlag = 0;
    errflg = 0;
    ofile = NULL;

    initErrorProcessing();

    while(1)
    {
        while((c = ourGetopt(argc, argv, (char *)"pPhdDM")) != EOF)
	{
	    switch(c)
	    {
		case 'p':
		    printTreeFlag = 1;
		    break;
		case 'P':
		    treePlusTypeFlag = 1;
		    break;
		case 'h':
		    usageFlag = 1;
		    break;
		case 'd':
		    yydebug = 1;
		    break;
		case 'D':
		    symbolTable->debug(true);
		    break;
		case 'M':
		    memFlag = 1;
		    break;
		case '?':
		    errflg = 1;
		    break;
	    }
	}

	//  Report any errors or usage request
        if(errflg)
        {
            (void)fprintf(stderr, "Usage: c- [options] [sourceFile]\n");
            exit(2);
        }

        //  Pick off a nonoption
        if(optind < argc)
	{
            //(void)printf("File: %s\n", argv[optind]);
	    if(yyin = fopen(argv[optind], "r"))
	    {
		//printf("====================================\n");
		//printf("FILE: %s\n", argv[optind]);
		string temp(argv[optind]);
		temp = temp.substr(0, temp.find_last_of("."));
		temp += ".tm";
		filename = temp.c_str();
		code = fopen(filename, "w");
		//printf("%s\n", filename);
                optind++;
	        break;
	    }
	    else
            {
                // File open failed
		printf("ERROR(ARGLIST): source file \"%s\" could not be opened.\n", argv[optind]);
		numErrors++;

		if(memFlag)
        	    printf("Offset for end of global space: %d\n", goffset);
		printf("Number of warnings: %d\n", numWarnings);
    		printf("Number of errors: %d\n", numErrors);
                exit(1);
            }
        }
        else
	{
            break;
        }
    }  

    yyparse();

    if(numErrors == 0)
    {
        if(usageFlag)              // -h
        {
            printf("Usage: c- [options] [sourceFile]\n");
        }

	if(printTreeFlag)  	   // -p
	{
	    printTree(syntaxTree, false, false);
	}
	
	semanticAnalysis(syntaxTree, symbolTable, ioLibrary);

	if(numErrors == 0)
	{
	    if(treePlusTypeFlag)   // -P
		printTree(syntaxTree, true, false);
	    
	    if(memFlag)		   // -M
	        printTree(syntaxTree, true, true);
	}

	//  Code generation will go here
	if(numErrors == 0)
	{
	    //code = fopen(filename, "w");
	    emitComment((char *)"=== Ride Like LIGHTNING, Crash Like THUNDER ===");
	    emitComment((char *)"C- Compiler Version C-S21");
	    emitComment((char *)"Author:         Miguel Villanueva");
	    emitComment((char *)"Built:          May 9, 2021");
	    emitComment((char *)"File compiled: ", argv[optind-1]);
	    int start = 0;
	    start = emitSkip(1);
	    codegenIO(ioLibrary);
	    codegen(syntaxTree, symbolTable);
	    backPatchAJumpToHere(start, (char *)"Jump to init [backpatch]");

	    //  Prolog Code
	    emitComment((char *)"INIT");
	    emitRM((char *)"LDA", FP, goffset, GP, (char *)"Set first frame at end of globals");
	    emitRM((char *)"ST", FP, 0, FP, (char *)"Store old fp (point to self)");
	    emitComment((char *)"INIT GLOBALS AND STATICS");
	    symbolTable->applyToAllGlobal(initGS);
	    emitComment((char *)"END INIT GLOBALS AND STATICS");
	    emitRM((char *)"LDA", AC, 1, PC, (char *)"Return address in ac");
	    TreeNode *main = (TreeNode *)symbolTable->lookupGlobal("main");
	    emitGotoAbs(main->loc, (char *)"Jump to main");
	    emitRO((char *)"HALT", 0, 0, 0, (char *)"DONE!");
	    emitComment((char *)"END INIT");
	    //fclose(code);
	}
    }

    if(code != NULL)
	fclose(code);

    if(memFlag && numErrors == 0)
	printf("Offset for end of global space: %d\n", goffset);

    //  Report the number of errors and warnings
    printf("Number of warnings: %d\n", numWarnings);
    printf("Number of errors: %d\n", numErrors);
    
    return 0;
}
