#include <stdio.h>
#include "calc.tab.h"

extern int yyparse();

int main(int argc, char** argv) {
    int result = yyparse();
    if (result == 0) {
        printf("programa sem erros sintáticos\n");
    } else {
        printf("programa com erros sintáticos\n");
    }
    return 0;
}