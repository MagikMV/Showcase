/* parser.y
 *
 * Miguel Villanueva
 * CS 445
 * February 19, 2021
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "scantype.h"
#include "ourGetopt.h"
#include "tree.h"

extern int yylex();
extern FILE *yyin;
extern int line;
extern int numErrors;
//  yydebug moved to subroutine section
//extern int yydebug;  // In calc.y example, placed in subroutine section

#define YYERROR_VERBOSE

//// any C/C++ functions you want here that might be used in grammar actions below
void yyerror(const char *msg)
{
    printf("ERROR(%d): %s\n", line, msg);
    numErrors++;  // Might be useful later
}

//// any C/C++ globals you want here that might be used in grammar actions below
TreeNode *syntaxTree;
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

%type <tree> program declList decl varDecl funDecl parms /*typeSpec*/ parmList parmTypeList
%type <tree> stmt matched unmatched simpleExp otherStmts iterRange expStmt compoundStmt
%type <tree> returnStmt breakStmt exp localDecls stmtList scopedVarDecl varDeclList
%type <tree> varDeclInit varDeclId parmIdList parmId mutable andExp unaryRelExp relExp
%type <tree> minmaxExp /*minmaxop relop*/ sumExp /*sumop*/ mulExp /*mulop*/ unaryExp /*unaryop*/ factor
%type <tree> immutable call constant args argList

%type <type> typeSpec
%type <tokenData> relop minmaxop sumop mulop unaryop
%token <tokenData> CHSIGN SIZEOF

%%

	/* Grammar */
program : declList									{ syntaxTree = $1; }
		;

declList: declList decl								{ $$ = addSibling($1, $2); }
		| decl										{ $$ = $1; }
		;

decl	: varDecl									{ $$ = $1; }
		| funDecl									{ $$ = $1; }
		;

varDecl	: typeSpec varDeclList ';'					{ $$ = $2; setType($$, $1, false); }
		/*typeSpec varDeclList ';'					{ $$ = addSibling($1, $2); }*/
		/*typeSpec varDeclList ';'					{ $$ = newDeclNode(VarK, Void, NULL, $1, $2); }*/
		;

scopedVarDecl: STATIC typeSpec varDeclList ';'		{ $$ = $3; setType($$, $2, true); }
		/*STATIC typeSpec varDeclList ';'			{ $$ = newDeclNode(VarK, Void, $1, $2, $3); }*/
		| typeSpec varDeclList ';'					{ $$ = $2; setType($$, $1, false); }
		/*typeSpec varDeclList ';'					{ $$ = newDeclNode(VarK, Void, NULL, $1, $2); }*/
		;

varDeclList: varDeclList ',' varDeclInit			{ $$ = addSibling($1, $3); }
		| varDeclInit								{ $$ = $1; }
		;

varDeclInit: varDeclId								{ $$ = $1; }
		| varDeclId ':' simpleExp					{ $1->child[0] = $3; $$ = $1; }
		/*varDeclId ':' simpleExp					{ $$ = addSibling($1, $3); }*/
		;

varDeclId: ID										{ $$ = newDeclNode(VarK, UndefinedType, $1); }
		| ID '[' NUMCONST ']'						{ $$ = newDeclNode(VarK, UndefinedType, $1); $$->isArray = true; }
		;

typeSpec: INT										{ $$ = Integer; }
		/*INT										{ $$ = newDeclNode(VarK, Integer, $1); }*/
		| BOOL										{ $$ = Boolean; }
		/*BOOL										{ $$ = newDeclNode(VarK, Boolean, $1); }*/
		| CHAR										{ $$ = Char; }
		/*CHAR										{ $$ = newDeclNode(VarK, Char, $1); }*/
		;

funDecl	: typeSpec ID '(' parms ')' stmt			{ $$ = newDeclNode(FuncK, $1, $2, $4, $6); }
		/*typeSpec ID '(' parms ')' stmt			{ $$ = newDeclNode(FuncK, Void, $2, $1, $4, $6); }*/
		| ID '(' parms ')' stmt						{ $$ = newDeclNode(FuncK, Void, $1, $3, $5); }
		;

parms	: parmList									{ $$ = $1; }
		| /* Epsilon */								{ $$ = NULL; }
		;

parmList: parmList ';' parmTypeList					{ $$ = addSibling($1, $3); }
		| parmTypeList								{ $$ = $1; }
		;

parmTypeList: typeSpec parmIdList					{ $$ = $2; setType($$, $1, false); }
		/*typeSpec parmIdList						{ $$ = newDeclNode(ParamK, Void, NULL, $1, $2); }*/
		;

parmIdList: parmIdList ',' parmId					{ $$ = addSibling($1, $3); }
		| parmId									{ $$ = $1; }
		;

parmId	: ID										{ $$ = newDeclNode(ParamK, UndefinedType, $1); }
		| ID '[' ']'								{ $$ = newDeclNode(ParamK, UndefinedType, $1); $$->isArray = true; }
		;

stmt	: matched									{ $$ = $1; }
		| unmatched									{ $$ = $1; }
		;

matched : IF simpleExp THEN matched ELSE matched	{ $$ = newStmtNode(IfK, $1, $2, $4, $6); }
		| WHILE simpleExp DO matched				{ $$ = newStmtNode(WhileK, $1, $2, $4); }
		| FOR ID '=' iterRange DO matched			{ $$ = newStmtNode(ForK, $1, newDeclNode(VarK, Integer, $2), $4, $6); }
		/*FOR varDeclId '=' iterRange DO matched	{ $$ = newStmtNode(ForK, $1, $2, $4, $6); }*/
		/*FOR ID '=' iterRange DO matched			{ $$ = newStmtNode(ForK, $2, $4, $6); }*/
		| otherStmts								{ $$ = $1; }
                ;

unmatched: IF simpleExp THEN matched				{ $$ = newStmtNode(IfK, $1, $2, $4); }
		| IF simpleExp THEN unmatched				{ $$ = newStmtNode(IfK, $1, $2, $4); }
		| IF simpleExp THEN matched ELSE unmatched	{ $$ = newStmtNode(IfK, $1, $2, $4, $6); }
		| WHILE simpleExp DO unmatched				{ $$ = newStmtNode(WhileK, $1, $2, $4); }
		| FOR ID '=' iterRange DO unmatched 		{ $$ = newStmtNode(ForK, $1, newDeclNode(VarK, Integer, $2), $4, $6); }
		/*FOR varDeclId '=' iterRange DO unmatched	{ $$ = newStmtNode(ForK, $1, $2, $4, $6); }*/
		/*FOR ID '=' iterRange DO unmatched			{ $$ = newStmtNode(ForK, $2, $4, $6); }*/
		;

otherStmts: expStmt									{ $$ = $1; }
		| compoundStmt			   					{ $$ = $1; }
		| returnStmt								{ $$ = $1; }
		| breakStmt									{ $$ = $1; }
		;
	   
expStmt	: exp ';'									{ $$ = $1; }
		| ';'										{ $$ = NULL; }
		;

compoundStmt: '{' localDecls stmtList '}'			{ $$ = newStmtNode(CompoundK, $1, $2, $3); }
		;

localDecls: localDecls scopedVarDecl				{ $$ = addSibling($1, $2); }
		| /* Epsilon */								{ $$ = NULL; }
		;

stmtList: stmtList stmt								{ $$ = addSibling($1, $2); }
		| /* Epsilon */								{ $$ = NULL; }
		;

iterRange: simpleExp TO simpleExp					{ $$ = newStmtNode(RangeK, $2, $1, $3); }
		| simpleExp TO simpleExp BY simpleExp		{ $$ = newStmtNode(RangeK, $2, $1, $3, $5); }
		;

returnStmt: RETURN ';'								{ $$ = newStmtNode(ReturnK, $1); }
		| RETURN exp ';'							{ $$ = newStmtNode(ReturnK, $1, $2); }
		;

breakStmt: BREAK ';'								{ $$ = newStmtNode(BreakK, $1); }
		;

exp		: mutable '=' exp							{ $$ = newExpNode(AssignK, $2, $1, $3); }
		| mutable ADDASS exp						{ $$ = newExpNode(AssignK, $2, $1, $3); }
		| mutable SUBASS exp						{ $$ = newExpNode(AssignK, $2, $1, $3); }
		| mutable MULASS exp						{ $$ = newExpNode(AssignK, $2, $1, $3); }
		| mutable DIVASS exp						{ $$ = newExpNode(AssignK, $2, $1, $3); }
		| mutable INC								{ $$ = newExpNode(AssignK, $2, $1); }
		| mutable DEC								{ $$ = newExpNode(AssignK, $2, $1); }
		| simpleExp									{ $$ = $1; }
		;

simpleExp: simpleExp OR andExp						{ $$ = newExpNode(OpK, $2, $1, $3); }
		| andExp									{ $$ = $1; }
		;

andExp	: andExp AND unaryRelExp					{ $$ = newExpNode(OpK, $2, $1, $3); }
		| unaryRelExp								{ $$ = $1; }
		;

unaryRelExp: NOT unaryRelExp						{ $$ = newExpNode(OpK, $1, $2); }
		| relExp									{ $$ = $1; }
		;

relExp	: minmaxExp relop minmaxExp					{ $$ = newExpNode(OpK, $2, $1, $3); }
		/*minmaxExp relop minmaxExp					{ $$ = newExpNode(OpK, NULL, $1, $2, $3); }*/ 
		| minmaxExp									{ $$ = $1; }
		;

relop	: LEQ										{ $$ = $1; }
		/*LEQ										{ $$ = newExpNode(OpK, $1); }*/
		| '<'										{ $$ = $1; }
		| '>'										{ $$ = $1; }
		| GEQ										{ $$ = $1; }
		| EQ										{ $$ = $1; }
		| NEQ										{ $$ = $1; }
		;

minmaxExp: minmaxExp minmaxop sumExp				{ $$ = newExpNode(OpK, $2, $1, $3); }
		| sumExp									{ $$ = $1; }
		;

minmaxop: MAX										{ $$ = $1; }
		/*MAX										{ $$ = newExpNode(OpK, $1); }*/
		| MIN										{ $$ = $1; }
		;

sumExp	: sumExp sumop mulExp						{ $$ = newExpNode(OpK, $2, $1, $3); }
		| mulExp									{ $$ = $1; }
		;

sumop	: '+'										{ $$ = $1; }
		/*'+'										{ $$ = newExpNode(OpK, $1); }*/
		| '-'										{ $$ = $1; }
		;

mulExp	: mulExp mulop unaryExp						{ $$ = newExpNode(OpK, $2, $1, $3); }
		| unaryExp									{ $$ = $1; }
		;

mulop	: '*'										{ $$ = $1; }
		/*'*'										{ $$ = newExpNode(OpK, $1); }*/
		| '/'										{ $$ = $1; }
		| '%'										{ $$ = $1; }
		;

unaryExp: unaryop unaryExp							{ $$ = newExpNode(OpK, $1, $2); }
		| factor									{ $$ = $1; }
		;

unaryop	: '-'										{ $1->tokenclass = CHSIGN; $$ = $1; }
		/*'-'										{ $$ = newExpNode(OpK, $1); }*/
		| '*'										{ $1->tokenclass = SIZEOF; $$ = $1; }
		| '?'										{ $$ = $1; }
		;

factor	: immutable									{ $$ = $1; }
		| mutable									{ $$ = $1; }
		;

mutable	: ID										{ $$ = newExpNode(IdK, $1); }
		| ID '[' exp ']'							{ $$ = newExpNode(OpK, $2, newExpNode(IdK, $1), $3); }
		/*ID '[' exp ']'							{ $$ = newExpNode(IdK, $1, $3); }*/
		;

immutable: '(' exp ')'								{ $$ = $2; }
		| call										{ $$ = $1; }
		| constant									{ $$ = $1; }
		;

call	: ID '(' args ')'							{ $$ = newExpNode(CallK, $1, $3); }
		;

args	: argList									{ $$ = $1; }
		| /* Epsilon */								{ $$ = NULL; }
		;

argList	: argList ',' exp							{ $$ = addSibling($1, $3); }
		| exp										{ $$ = $1; }
		;

constant: NUMCONST									{ $$ = newExpNode(ConstantK, $1); }
		| CHARCONST									{ $$ = newExpNode(ConstantK, $1); }
		| STRINGCONST								{ $$ = newExpNode(ConstantK, $1); $$->isArray = true; }
		| BOOLCONST									{ $$ = newExpNode(ConstantK, $1); }
		;

%%

	/* Subroutines */
//// any functions for main here

int main(int argc, char *argv[])
{
    int c;
    extern char *optarg;
    extern int optind;
    int printTreeFlag;
    extern int yydebug;  // Moved from definitions section
    int errflg;
    char *ofile;

    printTreeFlag = 0;
    ofile = NULL;

    while(1)
    {
        while((c = ourGetopt(argc, argv, (char *)"pd")) != EOF)
		{
			switch(c)
			{
				case 'p':
					printTreeFlag = 1;
					break;
				case 'd':
					yydebug = 1;
					break;
				case '?':
					errflg = 1;
			}
		}

		//  Report any errors or usage request
        if(errflg)
        {
            (void)fprintf(stderr, "Usage: cmd [-p] [-d] files...\n");
            exit(2);
        }

        //  Pick off a nonoption
        if(optind < argc)
		{
            //(void)printf("File: %s\n", argv[optind]);
			if(yyin = fopen(argv[optind], "r"))
			{
				optind++;
				break;
			}
			else
            {
                // File open failed
                //printf("ERROR: Failed to open \'%s\'\n", argv[1]);
                printf("ERROR: Failed to open \'%s\'\n", argv[optind]);
                exit(1);
            }
        }
        else
		{
            break;
        }
    }  

    numErrors = 0;
    yyparse();

    if(printTreeFlag)
    {
		printTree(syntaxTree);
    }

    //printf("Number of errors: %d\n", numErrors);  // Might need this later

    return 0;
}
