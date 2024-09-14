%{
/* includes, C defs */

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

struct decl *parser_result = 0;
extern int yylineno;
extern char* yytext;
int yylex();
void yyerror(const char *s);

%}

%union{
    struct decl *decl;
    struct stmt *stmt;
    struct expr *expr;
    struct type *type;
    struct param_list *param_list;
    char *name;
    int d;
}

%token ARRAY BOOLEAN FUNCTION INTEGER VOID 
%token TRUE FALSE
%token ELSE IF PRINT RETURN WHILE

%token <name> ID
%token <d> NUMBER

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

%type <decl> declaration_list declaration
%type <decl> var_declaration function_declaration var_declaration_list
%type <param_list> params param_list param
%type <type> simple_type array_type
%type <stmt> block return_stmt expression_stmt selection_stmt statement
%type <stmt> statement_list iteration_stmt print_stmt
%type <expr> expression simple_expression literal
%type <expr> conditional_expression_and conditional_expression_or
%type <expr> arithmetic_expression term factor
%type <expr> call var arg_list literal_list

%start program

%%

program
: declaration_list { parser_result = $1; }
;

declaration_list
: declaration_list declaration  { $$ = insert_decl($1, $2); }
| declaration   // { $$ = $1; }
;

declaration
: var_declaration 
| function_declaration
;

simple_type
: BOOLEAN { $$ = type_create(TYPE_BOOLEAN,0,0); }
| INTEGER { $$ = type_create(TYPE_INTEGER,0,0); }
| VOID    { $$ = type_create(TYPE_VOID,0,0); }
;

array_type
: ARRAY OPENBK NUMBER CLOSEBK simple_type { $$ = type_create(TYPE_ARRAY, $5, 0); }
;

literal_list
: literal
| literal_list COMMA literal { $$ = insert_expr($1, $3); }
;

literal
: TRUE { $$ = expr_create_boolean(1); }
| FALSE { $$ = expr_create_boolean(0); }
| NUMBER { $$ = expr_create_integer(atoi(yytext)); }
;

var_declaration  
: ID COLON simple_type SEMIC { $$ = var_decl_create($1, $3); }
| ID COLON simple_type ASSIGN literal SEMIC { $$ = var_decl_create($1, $3); $$->expr = $5; }
| ID COLON array_type SEMIC { $$ = array_decl_create($1, $3, 0); }
| ID COLON array_type ASSIGN OPENBRACE literal_list CLOSEBRACE SEMIC { $$ = array_decl_create($1, $3, 0); $$->expr = $6; }
;

params
: OPENP CLOSEP { $$ = 0; }
| OPENP param_list CLOSEP { $$ = $2; }
;

param_list
: param 
| param_list COMMA param  { $1 = insert_param($1, $3); $$ = $1; };

param
: ID COLON simple_type { $$ = param_create($1,$3); }
| ID COLON ARRAY OPENBK CLOSEBK simple_type { $$ = param_array_create($1, $6); }
;

function_declaration 
: ID COLON FUNCTION simple_type params ASSIGN block { $$ = func_decl_create($1,$4,$5,$7); }
;

block
: OPENBRACE var_declaration_list statement_list  CLOSEBRACE  { $$ = compound_stmt_create(STMT_BLOCK, $2, $3); }
| OPENBRACE var_declaration_list CLOSEBRACE { $$ = compound_stmt_create(STMT_BLOCK, $2, 0); }
| OPENBRACE statement_list CLOSEBRACE { $$ = compound_stmt_create(STMT_BLOCK, 0, $2); }
| OPENBRACE CLOSEBRACE { $$ = compound_stmt_create(STMT_BLOCK, 0, 0); }
;

var_declaration_list
: var_declaration_list var_declaration { $$ = insert_decl($1, $2); }
| var_declaration 
;

statement_list
: statement_list statement { $$ = insert_stmt($1, $2); }
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
: expression SEMIC { $$ = stmt_create(STMT_EXPR, 0, 0, $1, 0, 0, 0, 0); }
| SEMIC { $$ = 0; }

print_stmt
: PRINT OPENP expression CLOSEP SEMIC { $$ = stmt_create(STMT_PRINT, 0, 0, $3, 0, 0, 0, 0); }
;

selection_stmt
: IF OPENP expression CLOSEP statement { $$ = if_create($3, $5); }
| IF OPENP expression CLOSEP statement ELSE statement { $$ = if_else_create($3, $5, $7); }
;

iteration_stmt
: WHILE OPENP expression CLOSEP statement { $$ = while_create($3, $5); }
;

return_stmt
: RETURN expression SEMIC { $$ = stmt_create(STMT_RETURN, 0, 0, $2, 0, 0, 0, 0); }
| RETURN SEMIC { $$ = stmt_create(STMT_RETURN, 0, 0, 0, 0, 0, 0, 0); }
;

expression
: var ASSIGN expression { $$ = expr_create(EXPR_ASSIGN, $1, $3); }
| conditional_expression_or
;

var 
: ID { $$ = expr_create_var($1); }
| ID OPENBK expression CLOSEBK { $$ = expr_create_array($1,$3); }
;

conditional_expression_or:
  conditional_expression_and 
| conditional_expression_or OR conditional_expression_and  { $$ = expr_create(EXPR_OR, $1, $3); }
;

conditional_expression_and:
  simple_expression 
| conditional_expression_and AND simple_expression { $$ = expr_create(EXPR_AND, $1, $3); }
;

simple_expression 
: arithmetic_expression EQ arithmetic_expression { $$ = expr_create(EXPR_EQ, $1, $3); }
| arithmetic_expression NEQ arithmetic_expression { $$ = expr_create(EXPR_NEQ, $1, $3); }
| arithmetic_expression LT arithmetic_expression { $$ = expr_create(EXPR_LT, $1, $3); }
| arithmetic_expression LTE arithmetic_expression { $$ = expr_create(EXPR_LTEQ, $1, $3); }
| arithmetic_expression GT arithmetic_expression { $$ = expr_create(EXPR_GT, $1, $3); }
| arithmetic_expression GTE arithmetic_expression { $$ = expr_create(EXPR_GTEQ, $1, $3); }
| arithmetic_expression 
;

arithmetic_expression 
: arithmetic_expression PLUS term { $$ = expr_create(EXPR_ADD, $1, $3); }
| arithmetic_expression MINUS term  { $$ = expr_create(EXPR_SUB, $1, $3); }
| term
;

term  
: term TIMES factor { $$ = expr_create(EXPR_MUL, $1, $3); }
| term DIV factor { $$ = expr_create(EXPR_DIV, $1, $3); }
| factor
;

factor 
: NUMBER { $$ = expr_create_integer(atoi(yytext)); }
| FALSE  { $$ = expr_create_boolean(0); }
| TRUE   { $$ = expr_create_boolean(1); }
| var   
| call
| MINUS factor %prec UMINUS { $$ = expr_create(EXPR_SUB,expr_create_integer(0),$2); }
| NOT factor { $$ = expr_create(EXPR_NOT, $2, 0); }
| OPENP expression CLOSEP { $$ = $2; }
;

call 
: ID OPENP arg_list CLOSEP { $$ = expr_create_call($1,$3); }
| ID OPENP CLOSEP { $$ = expr_create_call($1, 0); }
;

arg_list 
: arg_list COMMA expression { $$ = insert_expr($1, $3); }
| expression
;

%%
void yyerror(const char *s)
{
   fprintf(stderr, "erro sintático.\n");
}
