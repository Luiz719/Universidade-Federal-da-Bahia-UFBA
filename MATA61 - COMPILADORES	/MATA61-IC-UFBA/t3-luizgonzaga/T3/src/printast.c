/* printast.c
 * Christina von Flach (github: christinaflach)
 * 2020, 2021, 2022, 2023
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "ast.h"

extern FILE *yyout;

void print_decl(struct decl *d);
void print_stmt(struct stmt *st);
void print_type(struct type *type);
void print_params(struct param_list *pl);
void print_var(struct decl *var);
void print_array(struct decl *array);
void print_func(struct decl *f);
void print_bexpr(char *c, struct expr *l, struct expr *r);
void print_expr(struct expr *e);
void print_name(char *name);
void bracket(struct decl *program);

void print_name(char *name) {
    fprintf(yyout,"[%s]", name);
}

void print_type(struct type *type) {
  struct type *t = type;
  if (t) {
    switch(t->kind) {
        case TYPE_VOID: {
            fprintf(yyout,"[void]");
            break;
        }
        case TYPE_INTEGER: {
            fprintf(yyout,"[int]");
            break;
        }
        case TYPE_ARRAY: {
            if (t->subtype)
                print_type(t->subtype);
            break;
        }
        case TYPE_FUNCTION: {
            if (t->subtype)
                print_type(t->subtype);
            break;
        }
        default: break;
     }
   }
}

void print_params(struct param_list *pl){
    struct param_list *p = pl;
    while (p) {
        fprintf(yyout,"\n[param ");
        print_type(p->type);
        fprintf(yyout,"[%s]",p->name);
        fprintf(yyout,"]");
        p = p->next;
    }
}

void print_var(struct decl *var) {
    if(var->expr==0){
        fprintf(yyout,"\n[var-declaration ");
        print_type(var->type);
        print_name(var->name);
    }
    fprintf(yyout,"]");
}

void print_array(struct decl *array) {
    fprintf(yyout,"\n[var-declaration ");
    struct type *t = array->type;
    print_type(array->type);
    print_name(array->name);
    print_expr(array->expr);
    fprintf(yyout,"]");
}

void print_func(struct decl *func) {
    fprintf(yyout,"\n[func-declaration \n");
    print_type(func->type);
    fprintf(yyout,"\n");
    print_name(func->name);
    fprintf(yyout,"\n[params");
    struct type *t = func->type;
    if (t->params)
        print_params(t->params);
    fprintf(yyout,"\n]");
    if (func->code)
       print_stmt(func->code);
    fprintf(yyout,"]");
}

void print_decl(struct decl *decl) {
  while (decl) {
    struct type *t = decl->type;
    switch(t->kind) {
        case TYPE_VOID: {
            fprintf(yyout,"[void]");
            break;
        }
        case TYPE_INTEGER: {
            print_var(decl);
            break;
        }
        case TYPE_ARRAY: {
            print_array(decl);
            break;
        }
        case TYPE_FUNCTION: {
            print_func(decl);
            break;
        }
        default: {
            fprintf(yyout,"tipo desconhecido\n");
            break;
        }
     }
     decl = decl->next;
   }
}

void print_stmt(struct stmt *s) {
  while (s) {
    switch(s->kind) {
        case STMT_EXPR: {
            if (s->expr)
                print_expr(s->expr);
            else
                fprintf(yyout,"\n[;]\n");
            break;
        }
        case STMT_IF_ELSE: {
            fprintf(yyout,"\n[selection-stmt ");
            print_expr(s->expr);
            print_stmt(s->body);
            if (s->else_body)
                print_stmt(s->else_body);
            fprintf(yyout,"]");
            break;
        }
        case STMT_WHILE: {
            fprintf(yyout,"\n[iteration-stmt ");
            print_expr(s->expr);
            print_stmt(s->body);
            fprintf(yyout,"]\n");
            break;
        }
        case STMT_PRINT: {
            fprintf(yyout,"\n[print-stmt ");
            if (s->expr)
                print_expr(s->expr);
            else
                fprintf(yyout,"[;]\n");
            fprintf(yyout,"]\n");
            break;
        }
        case STMT_RETURN: {
            fprintf(yyout,"\n[return-stmt ");
            if (s->expr)
                print_expr(s->expr);
            else
                fprintf(yyout,"[;]\n");
            fprintf(yyout,"]\n");
            break;
        }
        case STMT_BLOCK: {
            fprintf(yyout,"\n[compound-stmt ");
            if (s->decl)
                print_decl(s->decl);
            if (s->body)
                print_stmt(s->body);
            fprintf(yyout,"]\n");
            break;
        }
        default: break;
     }
     s = s->next;
  }
}

void print_bexpr(char *c, struct expr *l, struct expr *r) {
    fprintf(yyout,"\n[%s ",c);
    print_expr(l);
    if (r) print_expr(r);
    fprintf(yyout,"]");
}

void print_expr(struct expr *e) {
    if (e) {
    switch(e->kind) {
        case EXPR_ASSIGN: {
            print_bexpr("=", e->left, e->right);
            break;
        }
        case EXPR_ADD: {
            print_bexpr("+", e->left, e->right);
            break;
        }
        case EXPR_SUB:
        {
            print_bexpr("-", e->left, e->right);
            break;
        }
        case EXPR_MUL: {
            print_bexpr("*", e->left, e->right);
            break;
        }
        case EXPR_DIV:
        {
            print_bexpr("/", e->left, e->right);
            break;
        }
        case EXPR_NAME: {
            fprintf(yyout,"[%s]", e->name);
            break;
        }
        case EXPR_VAR: {
            fprintf(yyout,"[var ");
            print_expr(e->left);
            fprintf(yyout,"]");
            break;
        }
        case EXPR_ARRAY: {
            fprintf(yyout,"[var ");
            print_expr(e->left);
            print_expr(e->right);
            fprintf(yyout,"]");
            break;
        }
        case EXPR_INTEGER_LITERAL: {
            fprintf(yyout,"[");
            int i = e->integer_value;
            fprintf(yyout,"%d", i);
            fprintf(yyout,"]");
            break;
        }
        case EXPR_EQ:
        {
            print_bexpr("==", e->left, e->right);
            break;
        }
        case EXPR_NEQ:
        {
            print_bexpr("!=", e->left, e->right);
            break;
        }
        case EXPR_LT:
        {
            print_bexpr("<", e->left, e->right);
            break;
        }
        case EXPR_GT:
        {
            print_bexpr(">", e->left, e->right);
            break;
        }
        case EXPR_LTEQ:
        {
            print_bexpr("<=", e->left, e->right);
            break;
	}
        case EXPR_GTEQ:
        {
            print_bexpr(">=", e->left, e->right);
            break;
        }
        case EXPR_FUN: {
            break;
        }
        case EXPR_CALL: {
            fprintf(yyout,"\n[call ");
            fprintf(yyout,"\n");
            print_expr(e->left);
            fprintf(yyout,"\n[args ");
            print_expr(e->right);
            fprintf(yyout,"]\n");
            fprintf(yyout,"]");
            break;
        }
        case EXPR_ARG:  {
            print_expr(e->right);
            print_expr(e->left);
            break;
        }
        default: {
            fprintf(yyout,"internal error:\n");
        }
    }
  }
}


void bracket(struct decl *program) {
    fprintf(yyout,"[program ");
    print_decl(program);
    fprintf(yyout,"\n]\n");
}

