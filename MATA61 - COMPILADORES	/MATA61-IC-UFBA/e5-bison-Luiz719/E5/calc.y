%{
#include <stdio.h>
#include <stdlib.h>

int yylex();

void yyerror(const char* msg) {
      
}

%}


%token NUMBER
%token ADD 
%token SUB
%token ERROR
%token OPENPAR
%token CLOSEPAR

%%

expr: expr ADD expr | expr SUB expr | OPENPAR expr CLOSEPAR | NUMBER;

%%
