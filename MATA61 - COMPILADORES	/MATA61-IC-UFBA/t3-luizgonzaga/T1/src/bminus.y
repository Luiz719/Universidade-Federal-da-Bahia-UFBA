%{
#include <stdio.h>
#include <stdlib.h>
#include "token.h"

/* interface to lexer */
 
extern int yylineno; /* from lexer */
void yyerror(char *s, ...);
int yylex();
%}

/* declare tokens */ 
%token ID
%token KEY
%token NUM
%token SYM
%token SYMC
%token ERROR

%start program

%%
program: /* no syntactic rules yet */
;

%%

void yyerror(char *s, ...) { } 

