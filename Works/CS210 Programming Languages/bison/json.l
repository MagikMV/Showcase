%top{
    /* Miguel Villanueva */
    /* CS 210            */
    #include <stdio.h>
    #include "json.h"
    #include "tree.h"
    YYSTYPE yylval;
}

   /* Definitions Section */
%option yylineno
%option noyywrap

CODEPOINT		[^\"\\]
HEX			{DIGIT}[a-fA-F]
ESCAPE			[\\\/\b\f\n\t]|"\u"({HEX}{4})
STRING			{CODEPOINT}|{ESCAPE}
ZERO			[0]
COUNT			[1-9]
DIGIT			{ZERO}|{COUNT}
FRACTION		"."{DIGIT}+
EXPONENT		[eE][-+]?{DIGIT}+
NUM			{DIGIT}+{FRACTION}?{EXPONENT}?
	
%%
   /* Rules Section */
true			{ yylval.np = alcleaf(TRUE, yytext); return TRUE; }
false			{ yylval.np = alcleaf(FALSE, yytext); return FALSE; }
null			{ yylval.np = alcleaf(260, yytext); return 260; }
"{"			{ yylval.np = alcleaf(LCURLY, yytext); return LCURLY; }
"}"			{ yylval.np = alcleaf(RCURLY, yytext); return RCURLY; }
","			{ yylval.np = alcleaf(COMMA, yytext); return COMMA; }
":"			{ yylval.np = alcleaf(COLON, yytext); return COLON; }
"["			{ yylval.np = alcleaf(LBRACKET, yytext); return LBRACKET; }
"]"			{ yylval.np = alcleaf(RBRACKET, yytext); return RBRACKET; }
["]{STRING}*["]	 	{ yylval.np = alcleaf(STRINGLIT, yytext); return STRINGLIT; }
[-]?{NUM}		{ yylval.np = alcleaf(NUMBER, yytext); return NUMBER; }
[ \t\n]+                { /* skip */ }
.			{ printf("lexical error on line %d\n" , yylineno); }

