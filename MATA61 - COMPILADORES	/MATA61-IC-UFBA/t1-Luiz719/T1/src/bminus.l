%option noyywrap yylineno nodefault
%{

// yylineno    - variable to track line numbers 

#include "token.h"

%}


%%
array|boolean|else|false|function|if|integer|print|return|true|void|while {return KEY;}
[a-zA-Z][a-zA-Z\_0-9]{0,255} {return ID;}
"+"|"-"|"*"|"/"|"%"|"!"|"<"|">"|"="|":"|";"|","|"("|")"|"["|"]"|"{"|"}" {return SYM;}
"<="|">="|"=="|"!="|"&&"|"||" {return SYMC;}
[0-9]+ {return NUM; }
"//".*$  { /* ignore comments */ } 
[ \t\n\r]   { /* ignore whitespace */ }           
.   	{ return ERROR; }
%%


