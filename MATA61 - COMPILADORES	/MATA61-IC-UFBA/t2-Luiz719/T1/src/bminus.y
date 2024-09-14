%{
#include <stdio.h>
#include <stdlib.h>
#include "bminus.tab.h"

/* interface to lexer */
 
extern int yylineno; /* from lexer */
void yyerror(char *s, ...);
int yylex();
%}

/* declare tokens */ 
%token ARRAY BOOLEAN ELSE FALSE FUNCTION IF INTEGER PRINT TRUE VOID WHILE ID RETURN
%token PLUS MINUS MULT DIV MOD NOT LESS GREATER ASSIGN COLON SEMICOLON COMMA
%token LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE
%token LESS_OR_EQUAL GREATER_OR_EQUAL EQUALS NEQUAL AND OR NUM ERROR

%start program

%%
program:
    declaration-list
    ;

declaration-list:
    declaration-list declaration
    | declaration
    ;

declaration:
    var-declaration
    | function-declaration
    ;

simple-type:
    BOOLEAN
    | INTEGER
    ;

array-type:
    ARRAY LBRACKET NUM RBRACKET simple-type
    ;

literal-list:
    literal
    | literal-list COMMA literal
    ;

literal:
    TRUE
    | FALSE
    | NUM
    ;

var-declaration:
    ID COLON simple-type SEMICOLON
    | ID COLON simple-type ASSIGN literal SEMICOLON
    | ID COLON array-type SEMICOLON
    | ID COLON array-type ASSIGN LBRACE literal-list RBRACE SEMICOLON
    ;

params:
    LPAREN RPAREN
    | LPAREN param-list RPAREN
    ;

param-list:
    param
    | param-list COMMA param
    ;

param:
    ID COLON simple-type
    | ID COLON ARRAY LBRACKET RBRACKET simple-type
    ;

func-return:
    simple-type
    | VOID
    ;

function-declaration:
    ID COLON FUNCTION func-return params ASSIGN function-block
    ;

function-block:
    LBRACE var-declaration-list statement-list RBRACE
    | LBRACE var-declaration-list RBRACE
    | LBRACE statement-list RBRACE
    | LBRACE RBRACE
    ;

block:
    LBRACE var-declaration-list statement-list RBRACE
    | LBRACE var-declaration-list RBRACE
    | LBRACE statement-list RBRACE
    | LBRACE RBRACE
    ;
    
statement:
    IF LPAREN expression RPAREN statement-list SEMICOLON
    | IF LPAREN expression RPAREN statement-list ELSE statement-list SEMICOLON
    | WHILE LPAREN expression RPAREN function-block SEMICOLON
    | WHILE LPAREN expression RPAREN statement SEMICOLON
    | WHILE LPAREN expression RPAREN var-declaration SEMICOLON
    | print-statement SEMICOLON
    | expression SEMICOLON
    | return-statement SEMICOLON
    | block 
    ;

print-statement:
    PRINT NUM
    | PRINT var-call
    ;

return-statement:
    RETURN expression
    | RETURN 
    ;

function-call:
    ID args
    ;

args:
    LPAREN RPAREN
    | LPAREN args-list RPAREN
    ;

args-list:
    ID
    | args-list COMMA ID
    ;

var-declaration-list:
    var-declaration
    | var-declaration var-declaration-list
    ;

statement-list:
    statement
    | statement statement-list
    ;

expression:
    var-call ASSIGN expression 
    | simple_expression
    ;

var-call:
    ID 
    | ID LBRACKET NUM RBRACKET
    ;

simple_expression:
    additive_expression
    | additive_expression LESS additive_expression
    | additive_expression GREATER additive_expression
    | additive_expression GREATER_OR_EQUAL additive_expression
    | additive_expression LESS_OR_EQUAL additive_expression
    | additive_expression EQUALS additive_expression
    | additive_expression NEQUAL additive_expression
    | additive_expression AND additive_expression
    | additive_expression OR additive_expression
    ;

additive_expression:
    term
    | additive_expression PLUS term 
    | additive_expression MINUS term
    ;

term:
    factor
    | term MULT factor 
    | term DIV factor 
    | term MOD factor 
    ;

factor:
    NUM
    | NOT factor
    | LPAREN expression RPAREN
    | var-call
    | function-call
    ;   

%%

void yyerror(char *s, ...) { } 

