/* parser.y
 *
 * Miguel Villanueva
 * CS 445
 * January 30, 2021
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "scantype.h"

extern int yylex();
extern FILE *yyin;
extern int line;
extern int numErrors;
extern int yydebug;  // In calc.y example, placed in subroutine section

#define YYERROR_VERBOSE

//// any C/C++ functions you want here that might be used in grammar actions below
void yyerror(const char *msg)
{
    printf("ERROR(%d): %s\n", line, msg);
    numErrors++;  // Might be useful later
}

//// any C/C++ globals you want here that might be used in grammar actions below
%}

//// your %union statement
%union
{
    TokenData *tokenData;
}
	/* Declarations */
//// your %token statements defining token classes
%token <tokenData> '%' '*' '(' ')' '-' '{' '}' '[' ']'
%token <tokenData> ':' ';' '<' '>' '?' ',' '/' '=' '+'
%token <tokenData> ADDASS ID INT NUMCONST IF EQ RETURN STRINGCONST THEN ELSE DEC CHARCONST
%token <tokenData> BOOL CHAR STATIC AND OR NOT BOOLCONST FOR TO BY DO BREAK WHILE
%token <tokenData> INC MIN MAX GEQ LEQ NEQ

%%

	/* Grammar */
tokenlist     : tokenlist token
              | token 
              ;

token : '%' 	     { printf("Line %d Token: %s\n", $1->linenum, $1->tokenstr); }
      | '*' 	     { printf("Line %d Token: %s\n", $1->linenum, $1->tokenstr); }
      | '(' 	     { printf("Line %d Token: %s\n", $1->linenum, $1->tokenstr); }
      | ')' 	     { printf("Line %d Token: %s\n", $1->linenum, $1->tokenstr); }
      | '-'          { printf("Line %d Token: %s\n", $1->linenum, $1->tokenstr); }
      | '{'          { printf("Line %d Token: %s\n", $1->linenum, $1->tokenstr); }
      | '}'          { printf("Line %d Token: %s\n", $1->linenum, $1->tokenstr); }
      | '['          { printf("Line %d Token: %s\n", $1->linenum, $1->tokenstr); }
      | ']'          { printf("Line %d Token: %s\n", $1->linenum, $1->tokenstr); }
      | ':'          { printf("Line %d Token: %s\n", $1->linenum, $1->tokenstr); }
      | ';'          { printf("Line %d Token: %s\n", $1->linenum, $1->tokenstr); }
      | '<'          { printf("Line %d Token: %s\n", $1->linenum, $1->tokenstr); }
      | '>'          { printf("Line %d Token: %s\n", $1->linenum, $1->tokenstr); }
      | '?'          { printf("Line %d Token: %s\n", $1->linenum, $1->tokenstr); }
      | ','          { printf("Line %d Token: %s\n", $1->linenum, $1->tokenstr); }
      | '/'          { printf("Line %d Token: %s\n", $1->linenum, $1->tokenstr); }
      | '='          { printf("Line %d Token: %s\n", $1->linenum, $1->tokenstr); }
      | '+'	         { printf("Line %d Token: %s\n", $1->linenum, $1->tokenstr); }
      | ADDASS	     { printf("Line %d Token: ADDASS\n", $1->linenum); }
      | ID	         { printf("Line %d Token: ID Value: %s\n", $1->linenum, $1->tokenstr); }
      | INT	         { printf("Line %d Token: INT\n", $1->linenum); }
      | NUMCONST     { printf("Line %d Token: NUMCONST Value: %d  Input: %s\n", $1->linenum, $1->nvalue, $1->tokenstr); }
      | IF	         { printf("Line %d Token: IF\n", $1->linenum); }
      | EQ	         { printf("Line %d Token: EQ\n", $1->linenum); }
      | RETURN       { printf("Line %d Token: RETURN\n", $1->linenum); }
      | STRINGCONST  { printf("Line %d Token: STRINGCONST Value: \"%s\"  Len: %d  Input: %s\n", $1->linenum, $1->svalue, strlen($1->svalue), $1->tokenstr); }
      | THEN	     { printf("Line %d Token: THEN\n", $1->linenum); }
      | ELSE	     { printf("Line %d Token: ELSE\n", $1->linenum); }
      | DEC	         { printf("Line %d Token: DEC\n", $1->linenum); }
      | CHARCONST    { printf("Line %d Token: CHARCONST Value: \'%c\'  Input: %s\n", $1->linenum, $1->cvalue, $1->tokenstr); }
      | BOOL	     { printf("Line %d Token: BOOL\n", $1->linenum); }
      | CHAR	     { printf("Line %d Token: CHAR\n", $1->linenum); }
      | STATIC	     { printf("Line %d Token: STATIC\n", $1->linenum); }
      | AND          { printf("Line %d Token: AND\n", $1->linenum); }
      | OR	         { printf("Line %d Token: OR\n", $1->linenum); }
      | NOT	         { printf("Line %d Token: NOT\n", $1->linenum); }
      | BOOLCONST    { printf("Line %d Token: BOOLCONST Value: %d  Input: %s\n", $1->linenum, $1->nvalue, $1->tokenstr); }
      | FOR	         { printf("Line %d Token: FOR\n", $1->linenum); }
      | TO	         { printf("Line %d Token: TO\n", $1->linenum); }
      | BY	         { printf("Line %d Token: BY\n", $1->linenum); }
      | DO	         { printf("Line %d Token: DO\n", $1->linenum); }
      | BREAK        { printf("Line %d Token: BREAK\n", $1->linenum); }
      | WHILE	     { printf("Line %d Token: WHILE\n", $1->linenum); }
      | INC	         { printf("Line %d Token: INC\n", $1->linenum); }
      | MIN	         { printf("Line %d Token: MIN\n", $1->linenum); }
      | MAX	         { printf("Line %d Token: MAX\n", $1->linenum); }
      | GEQ	         { printf("Line %d Token: GEQ\n", $1->linenum); }
      | LEQ	         { printf("Line %d Token: LEQ\n", $1->linenum); }
      | NEQ	         { printf("Line %d Token: NEQ\n", $1->linenum); }
      ; 
//// put all your tokens here and individual actions 
//// DO NOT DO THE C- GRAMMAR (this is a test program) 
//// the grammar for assignment 1 is super simple

%%

	/* Subroutines */
//// any functions for main here

int main(int argc, char *argv[])
{
    ////  some of your stuff here
    if(argc > 1)
    {
        if(yyin = fopen(argv[1], "r"))
	    {
	        // File open successful
	    }
	    else
	    {
	        // File open failed
	        printf("ERROR: Failed to open \'%s\'\n", argv[1]);
	        exit(1);
	    }
    }
    numErrors = 0;
    yyparse();

    //printf("Number of errors: %d\n", numErrors);  // Might need this later

    return 0;
}
