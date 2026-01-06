/* Miguel Villanueva
 * CS 210
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include "prodrules.h"
#include "tree.h"
void yyerror(char *s);

extern int yylineno;
extern char *yyfilename;
extern char *yytext;
struct node *yyroot;
%}

%union
{
    struct node *np;
}

	/* Declarations */
%token <np> TRUE
%token <np> FALSE
%token <np> null
%token <np> LCURLY
%token <np> RCURLY
%token <np> COMMA
%token <np> COLON
%token <np> LBRACKET
%token <np> RBRACKET
%token <np> STRINGLIT
%token <np> NUMBER

%type <np> json object members member array elements element value 

%%
	/* Grammar */
json
    : element                     { yyroot = $1; }
    ;

object 
    : LCURLY RCURLY               { $$ = alcnary(OBJ, OBJ_R1, 2, $1, $2); }
    | LCURLY members RCURLY       { $$ = alcnary(OBJ, OBJ_R2, 3, $1, $2, $3); }
    ;

members 
    : member                      { $$ = alcnary(MEMS, MEMS_R1, 1, $1); }
    | member COMMA members        { $$ = alcnary(MEMS, MEMS_R2, 3, $1, $2, $3); }
    ;

member
    : STRINGLIT COLON element     { $$ = alcnary(MEM, MEM_R1, 3, $1, $2, $3); }
    ;

array
    : LBRACKET RBRACKET           { $$ = alcnary(ARY, ARY_R1, 2, $1, $2); }
    | LBRACKET elements RBRACKET  { $$ = alcnary(ARY, ARY_R2, 3, $1, $2, $3); }
    ;

elements
    : element                     { $$ = alcnary(ELMS, ELMS_R1, 1, $1); }
    | element COMMA elements      { $$ = alcnary(ELMS, ELMS_R2, 3, $1, $2, $3); }
    ;

element
    : value                       { $$ = alcnary(ELM, ELM_R1, 1, $1); }
    ;

value
    : object                      { $$ = alcnary(VAL, VAL_R1, 1, $1); }
    | array                       { $$ = alcnary(VAL, VAL_R2, 1, $1); }
    | STRINGLIT                   { $$ = alcleaf(STRINGLIT, yytext); }
    | NUMBER                      { $$ = alcleaf(NUMBER, yytext); }
    | TRUE                        { $$ = alcleaf(TRUE, yytext); }
    | FALSE                       { $$ = alcleaf(FALSE, yytext); }
    | null                        { $$ = alcleaf(null, yytext); } 
    ;

%%
	/* Subroutines */
void yyerror(char *s)
{
    fprintf(stderr, "%s:%d: %s before '%s' token\n",
	    yyfilename, yylineno, s, yytext);
}
