
# Exercício E5 - Aquecimento com Bison 

- Copiar para a pasta E5 os seus arquivos .l e .y que estão na pasta E1 (exercício E1)

- Alterar calc.y para criar regras de produção para a gramática:
``` 
calc -> expr EOL
;

expr -> expr + expr
     |  expr - expr
     |  ( expr )
     |  NUM
;
```

- Alterar calc.y para definir novo(s) token(s), se necessário;
Remover o token para o símbolo '|'.

- Alterar calc.y para usar nas regras de produção os nomes de tokens definidos com %token

- Criar um novo arquivo, ```main.c''' e mover a função main() para esse arquivo; fazer ajustes necessários (include, etc.)

- Modificar a função main() para chamar yyparse() e não mais yylex();
A depender do resultado retornado por yyparse(), imprimir na saída padrão "programa sem erros sintáticos" ou "programa com erros sintáticos" 

- Rodar flex, bison (```bison -d calc.y''') e gerar executável ``calc''.

*Importante*: 
- Aceitar convite enviado via Github Classroom e 
submeter sua resposta via repositório criado automaticamente para este exercício do Github Classroom.  
- Respostas em repositórios pessoais não serão consideradas.
- Não modificar a estrutura nem a visibilidade do repositório.

