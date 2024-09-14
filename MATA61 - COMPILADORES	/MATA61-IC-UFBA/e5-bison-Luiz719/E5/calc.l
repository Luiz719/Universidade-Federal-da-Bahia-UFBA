/* 
 * Example 1-4. Calculator scanner fb1-4.l, from Levine book, p. 7-8.
 * Scanner recognizes tokens for the calculator and prints them out.
 *  - yylval is the variable that stores the token value, an integer;
*/
%option noyywrap nodefault yylineno

%{
#include "calc.tab.h"

void yyerror(char *s);

%}

DIGIT [0-9]                   
%%
"("   { return OPENPAR; }
")"   { return CLOSEPAR; }
"+"     { return ADD; }
"-"     { return SUB; }
{DIGIT}+(\.{DIGIT}{1,2})? { return NUMBER; }

[ \t\n]   { /* ignore whitespace */ }           
.   	{ return ERROR; }
%%

