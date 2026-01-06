/* main.c 
 *
 * Miguel Villanueva
 * CS 210
 */
#include "json.tab.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

extern FILE *yyin;
extern char *yytext;
char *yyfilename;
extern struct node *yyroot;


int main(int argc, char *argv[])
{
    int i;
    if (argc < 2) { printf("usage: iscan file.dat\n"); exit(-1); }
    yyin = fopen(argv[1],"r");
    if (yyin == NULL) { printf("can't open/read '%s'\n", argv[1]); exit(-1); }
    yyfilename = argv[1];
    if ((i=yyparse()) != 0) {
       printf("parse failed\n");
       }
    else { printf("no errors\n"); }

    printf("\n");
    printTree(yyroot);
    printf("\n");
    return 0;
}

/*
      tree.h Function Definitions
*/

struct node *treenode(int symbol)
{
    struct node *p = (struct node *)calloc(1, sizeof(struct node));
    p->symbol = symbol;
    return p;
}

struct node *alcleaf(int symbol, char *lexeme)
{
    struct node *ret = treenode(symbol);
    ret->u.t.lexeme = strdup(lexeme);
    return;
}

struct node *alcnary(int symbol, int prodrule, int nkids, ...)
{
    int i;
    va_list mylist;
    struct node *rv = treenode(symbol);
    rv->u.nt.production_rule = prodrule;
    va_start(mylist, nkids);
    for(i = 0; i < nkids; i++)
    {
        rv->u.nt.child[i] = va_arg(mylist, struct node *);
    }
    va_end(mylist);
    return rv;
}

void printTree(struct node *np)
{
    if (np->symbol < 1000)
    {
	printf("Symbol: %s\n", np->u.t.lexeme);
	fflush(stdout);
    }
    else
    {
	int i;
	for(i = 0; np->u.nt.child[i] != NULL; i++)
	{
	    printTree(np->u.nt.child[i]);
	}
    }
}
