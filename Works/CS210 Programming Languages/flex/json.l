%top{
    /* Miguel Villanueva */
    /* CS 210            */
    #include <stdio.h>
    #include "json.h"
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
true			{ return TRUE; }
false			{ return FALSE; }
null			{ return 3; }
"{"			{ return LCURLY; }
"}"			{ return RCURLY; }
","			{ return COMMA; }
":"			{ return COLON; }
"["			{ return LBRACKET; }
"]"			{ return RBRACKET; }
["]{STRING}*["]	 	{ return STRINGLIT; }
[-]?{NUM}		{ return NUMBER; }
[ \t\n]+                { /* skip */ }
.			{ printf("lexical error on line %d\n" , yylineno); }

