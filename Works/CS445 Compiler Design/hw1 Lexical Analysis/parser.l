%{
    /* Miguel Villaueva */
    /* CS 445 */
    /* January 30, 2021 */

    #include <stdio.h>
    #include <stdlib.h>
    #include "scantype.h"
    #include "parser.tab.h"

    int line = 1;   // Variable for line number
    int numErrors;  // Variable for error count (might be useful in later assignment)

    static int setValue(int lineNum, int tokenClass, char *svalue)
    {
        yylval.tokenData = new TokenData;
		yylval.tokenData->tokenclass = tokenClass;
		yylval.tokenData->linenum = lineNum;
		yylval.tokenData->tokenstr = strdup(svalue);

		int i = 1;
		int count = 1;
		char *litValue = (char *) malloc(sizeof(char) * count);
		int j = 1;
		int count2 = 0;
		switch(tokenClass)
		{
			case NUMCONST:
				yylval.tokenData->nvalue = atoi(svalue);
				break;
			case STRINGCONST:
				//int i = 1;
				//int count = 1;
				//char *litValue = (char *) malloc(sizeof(char) * count);
				while(i < strlen(svalue) - 1)
				{
					if(svalue[i] == '\\')
					{
						if(svalue[i + 1] == '\\')
						{
							litValue[count - 1] = svalue[i + 1];
							i = i + 2;
							count++;
							litValue = (char *) realloc(litValue, sizeof(char) * count);
						}
						else if(svalue[i + 1] == 'n')
						{
							litValue[count - 1] = '\n';
							i = i + 2;
							count++;
							litValue = (char *) realloc(litValue, sizeof(char) * count);
						}
						else if(svalue[i + 1] != 'n')
						{
							litValue[count - 1] = svalue[i + 1];
							i = i + 2;
							count++;
							litValue = (char *) realloc(litValue, sizeof(char) * count);
						}
					}
					else if(svalue[i] != '\\')
					{
						litValue[count - 1] = svalue[i];
						//printf("litValue[i]: %c\n", litValue[count - 1]);
						i++;
						count++;
						litValue = (char *) realloc(litValue, sizeof(char) * count);
					}
				}
				litValue[count - 1] = 0;
				yylval.tokenData->svalue = strdup(litValue);
				break;
			case CHARCONST:
				//int j = 1;
				//int count2 = 0;
				while(j < strlen(svalue) - 1)
				{
					if(svalue[1] == '\\' && j == 1)
					{
						if(svalue[2] == '\\')
						{
							yylval.tokenData->cvalue = '\\';
							count2 = 1;
							j = j + 2;
						}
						else if(svalue[2] == '0')
						{
							yylval.tokenData->cvalue = '\0';
							count2 = 1;
							j = j + 2;
						}
						else if(svalue[2] == 'n')
						{
							yylval.tokenData->cvalue = '\n';
							count2 = 1;
							j = j + 2;
						}
						else
						{
							yylval.tokenData->cvalue = svalue[2];
							count2 = 1;
							j = j + 2;
						}
					}
					else if(j == 1)
					{
						yylval.tokenData->cvalue = svalue[1];
						j++;
						count2 = 1;	
					}
					else if(svalue[j] == '\\')
					{
						j = j + 2;
						count2++;
					}
					else
					{
						j++;
						count2++;
					}
				}
				if(count2 != 1)
				{
					printf("WARNING(%d): character is %d characters long and not a single character: \'%s\'.  The first char will be used.\n", lineNum, count2, svalue); 
				}
				break;
			case BOOLCONST:
				yylval.tokenData->nvalue = 1;
				if(svalue[0] == 'f')
				{
					yylval.tokenData->nvalue = 0;
				}
				/*else
				{
					printf("test\n");
					yylval.tokenData->nvalue = 1;
				}*/
				break;
		}
		return tokenClass;
    }
%}

    /* Definitions Section */
%option noyywrap

%%
    /* Rules Section */
[%*()\-{}\[\]]			{ return setValue(line, yytext[0], yytext); }
[:;<>?,\/=\+]      		{ return setValue(line, yytext[0], yytext); }
\/\/.*					{ /* do nothing */ }
"+="	    			{ return setValue(line, ADDASS, yytext); }
"int"					{ return setValue(line, INT, yytext); }
"if"					{ return setValue(line, IF, yytext); }
"return"				{ return setValue(line, RETURN, yytext); }
"then"					{ return setValue(line, THEN, yytext); }
"else"					{ return setValue(line, ELSE, yytext); }
"bool"					{ return setValue(line, BOOL, yytext); }
"char"					{ return setValue(line, CHAR, yytext); }
"static"				{ return setValue(line, STATIC, yytext); }
"and"					{ return setValue(line, AND, yytext); }
"or"					{ return setValue(line, OR, yytext); }
"not"					{ return setValue(line, NOT, yytext); }
"true"|"false"			{ return setValue(line, BOOLCONST, yytext); }
"for"					{ return setValue(line, FOR, yytext); }
"to"					{ return setValue(line, TO, yytext); }
"by"					{ return setValue(line, BY, yytext); }
"do"					{ return setValue(line, DO, yytext); }
"break"					{ return setValue(line, BREAK, yytext); }
"while"					{ return setValue(line, WHILE, yytext); }
    /* ["][^\"]*["]		{ return setValue(line, STRINGCONST, yytext); } */
["]([^\"\n]|"\\\"")*["]	{ return setValue(line, STRINGCONST, yytext); }
[']([^\'\n]|"\\\'")*[']	{ return setValue(line, CHARCONST, yytext); }
[a-zA-Z][0-9a-zA-Z]*	{ return setValue(line, ID, yytext); }
[1-9][0-9]*|0			{ return setValue(line, NUMCONST, yytext); }
"=="					{ return setValue(line, EQ, yytext); }
"--"					{ return setValue(line, DEC, yytext); }
"++"					{ return setValue(line, INC, yytext); }
":<:"					{ return setValue(line, MIN, yytext); }
":>:"					{ return setValue(line, MAX, yytext); }
">="					{ return setValue(line, GEQ, yytext); }
"<="					{ return setValue(line, LEQ, yytext); }
"!="					{ return setValue(line, NEQ, yytext); }
[ \t]					{ /* do nothing */ }
\n	    				{ line ++; }
.	    				{ printf("ERROR(%d): Invalid or misplaced input character: \'%s\'. Character Ignored.\n", line, yytext); }

%%
    /* Subroutines Section */
