// main.c for T2 - Syntax Analysis for B-

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "bminus.tab.h" 

/* interface to parser  */

extern char *yytext;
extern FILE *yyin;
extern int yyparse();
extern void yyerror (const char *);

int main(int argc, char **argv) {
    int token;

    FILE *fout; 

    if (argc > 2) {
        if(!(yyin = fopen(argv[1], "r"))) {
            fprintf(stderr, "erro na abertura do arquivo de entrada %s.\n",argv[1]);
            return (1); 
        }
    	if(!(fout = fopen(argv[2], "w"))) {
            fprintf(stderr,"erro na criacao do arquivo de saida %s.\n",argv[2]);
            return (1);
        }
        if (yyparse())
	   fprintf(fout, "erro sintático.\n");

    }
    else {
        fprintf(stderr,"erro no número de argumentos de entrada.\n");
        return (1);
    }
    fclose(fout);
}

