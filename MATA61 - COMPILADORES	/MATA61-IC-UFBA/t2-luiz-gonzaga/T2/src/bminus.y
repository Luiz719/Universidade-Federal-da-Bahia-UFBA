%{
/* includes, C defs */

#include <stdio.h>
#include <stdlib.h>

extern int yylineno;
int yylex();
void yyerror(const char *s);

%}

%token ARRAY BOOLEAN FUNCTION INTEGER VOID 
%token TRUE FALSE
%token ELSE IF PRINT RETURN WHILE

%token ID
%token NUMBER

%token PLUS MINUS TIMES DIV
%token NOT
%token ASSIGN
%token LT GT
%token SEMIC
%token COMMA 
%token COLON
%token OPENP CLOSEP 
%token OPENBK CLOSEBK
%token OPENBRACE CLOSEBRACE
%token LTE GTE EQ NEQ 
%token AND OR

%token ERROR

%nonassoc ASSIGN
%nonassoc LT LTE GT GTE EQ NEQ  // relacional
%nonassoc AND
%nonassoc OR
%nonassoc NOT
%left UMINUS


%start program

%%

program
: declaration_list
;

declaration_list
: declaration_list declaration
| declaration
;

declaration
: var_declaration
| function_declaration 
;

simple_type
: BOOLEAN
| INTEGER
;

array_type
: ARRAY OPENBK NUMBER CLOSEBK simple_type
;

literal_list
: literal
| literal_list COMMA literal
;

literal
: TRUE
| FALSE
| NUMBER
;

var_declaration
: ID COLON simple_type SEMIC
| ID COLON simple_type ASSIGN literal SEMIC
| ID COLON array_type SEMIC
| ID COLON array_type ASSIGN OPENBRACE literal_list CLOSEBRACE SEMIC
;

params
: OPENP CLOSEP
| OPENP param_list CLOSEP
;

param_list
: param
| param_list COMMA param  

param
: ID COLON simple_type /* falta parametro do tipo array */
| ID COLON ARRAY OPENBK CLOSEBK simple_type
;

function_declaration 
: ID COLON FUNCTION simple_type params ASSIGN block
| ID COLON FUNCTION VOID params ASSIGN block
;

block
: OPENBRACE var_declaration_list statement_list  CLOSEBRACE
| OPENBRACE var_declaration_list CLOSEBRACE
| OPENBRACE statement_list  CLOSEBRACE
| OPENBRACE CLOSEBRACE
;

var_declaration_list
: var_declaration_list var_declaration
| var_declaration
;

statement_list
: statement_list statement
| statement
;

statement
: expression_stmt 
| block
| selection_stmt
| iteration_stmt 
| return_stmt
| print_stmt
;

expression_stmt
: expression SEMIC
| SEMIC

print_stmt
: PRINT OPENP expression CLOSEP SEMIC
;

selection_stmt
: IF OPENP expression CLOSEP statement
| IF OPENP expression CLOSEP statement ELSE statement
;

iteration_stmt
: WHILE OPENP expression CLOSEP statement
;

return_stmt
: RETURN expression SEMIC
| RETURN SEMIC
;

expression
: var ASSIGN expression 
| conditional_expression_or
;

var 
: ID 
| ID OPENBK NUMBER CLOSEBK
| ID OPENBK ID CLOSEBK
;

conditional_expression_or:
  conditional_expression_and
| conditional_expression_or OR conditional_expression_and
;

conditional_expression_and:
  simple_expression
| conditional_expression_and AND simple_expression
;

simple_expression
: arithmetic_expression EQ arithmetic_expression
| arithmetic_expression NEQ arithmetic_expression
| arithmetic_expression LT arithmetic_expression
| arithmetic_expression LTE arithmetic_expression
| arithmetic_expression GT arithmetic_expression
| arithmetic_expression GTE arithmetic_expression
| arithmetic_expression
;

arithmetic_expression
: arithmetic_expression PLUS term
| arithmetic_expression MINUS term
| term
;

term
: term TIMES factor
| term DIV factor
| factor
;

factor 
: NUMBER
| var 
| call
| MINUS factor %prec UMINUS
| NOT factor
| OPENP expression CLOSEP
;

call 
: ID OPENP arg_list CLOSEP
| ID OPENP CLOSEP
;

arg_list 
: arg_list COMMA expression 
| expression
;

%%
void yyerror(const char *s)
{
   fprintf(stderr, "erro sintático.\n");
}
