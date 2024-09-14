%option noyywrap yylineno nodefault
%{

// yylineno    - variable to track line numbers 

#include "bminus.tab.h"

%}

%%
array    { return ARRAY; }
boolean  { return BOOLEAN; }
else     { return ELSE; }
false    { return FALSE; }
function { return FUNCTION; }
if       { return IF; }
integer  { return INTEGER; }
print    { return PRINT; }
true     { return TRUE; }
void     { return VOID; }
while    { return WHILE; }
return   { return RETURN; }
[a-zA-Z][a-zA-Z\_0-9]{0,255} {return ID;}
"+"    { return PLUS; }
"-"    { return MINUS; }
"*"    { return MULT; }
"/"    { return DIV; }
"%"    { return MOD; }
"!"    { return NOT; }
"<"    { return LESS; }
">"    { return GREATER; }
"="    { return ASSIGN; }
":"    { return COLON; }
";"    { return SEMICOLON; }
","    { return COMMA; }
"("    { return LPAREN; }
")"    { return RPAREN; }
"["    { return LBRACKET; }
"]"    { return RBRACKET; }
"{"    { return LBRACE; }
"}"    { return RBRACE; }
"<="   { return LESS_OR_EQUAL; }
">="   { return GREATER_OR_EQUAL; }
"=="   { return EQUALS; }
"!="   { return NEQUAL; }
"&&"   { return AND; }
"||"   { return OR; }
[0-9]+ {return NUM; }
"//".*$  { /* ignore comments */ } 
[ \t\n\r]   { /* ignore whitespace */ }           
.   	{ return ERROR; }
%%


