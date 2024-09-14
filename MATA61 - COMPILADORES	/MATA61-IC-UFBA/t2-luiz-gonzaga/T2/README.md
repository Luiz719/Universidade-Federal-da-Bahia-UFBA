# Projeto de um Compilador

## Trabalho 2 (T2): Análise Sintática

Nesta parte do projeto, você irá implementar um analisador sintático _bottom-up_ 
para a linguagem B-, usando a ferramenta _Bison_,
e integrá-lo com uma nova versão do analisador léxico desenvolvido com Flex no T1.

O analisador sintático deve receber uma sequência de _tokens_ 
enviados pelo analisador léxico desenvolvido no trabalho 1 (T1)
e determinar se um programa B- segue ou não 
a especificação definida por sua gramática.
Se um erro sintático for detectado, 
apenas a mensagem de erro padrão do Bison será reportada e 
a análise sintática interrompida. 

Antes de iniciar a sua implementação, recomendamos como leitura complementar o capítulo 5
do livro "Introduction to Compilers and Language Design" de Douglas Thain.
Outra consulta interessante é uma [especificação yacc para ANSI C](https://www.lysator.liu.se/c/ANSI-C-grammar-y.html) feita no século passado (década de 80).

## Bison e Flex

O Bison deverá ser utilizado para geração do analisador sintático,
trabalhando em conjunto com o analisador léxico 
gerado com Flex (T1).
Na pasta ```src''' colocamos o arquivo ```lex.yy.c''' (não apagar ou modificar),
que deve ser compilado com os demais arquivos para gerar o executável ```bminus'''.

### bminus.y

```$ bison -d bminus.y```

A opção -d faz com que o Bison gere o arquivo _bminus.tab.h_, 
que faz a interface com o analisador léxico gerado pelo Flex.

- A definição dos tokens com a diretiva ```%token``` foi modificada para usar códigos mais específicos, por exemplo:
   - IF, WHILE, etc., para palavras reservadas, ao invés da categoria geral "KEY" usada em T1;
   - PLUS, MINUS, etc., para símbolos, ao invés da da categoria geral "SYM" usada em T1;
   - EQ, NEQ, AND, etc., para símbolos compostos, ao invés da da categoria geral "SYMC" usada em T1;

```
%token IF 
...
%token PLUS

%token EQ

%token COMMA
...
``` 

- As regras de produção da gramática para B- devem ser especificadas no programa bminus.y.

__Atenção: Colocar os nomes dos membros da equipe como comentário no arquivo bminus.y.__

### main.c

A função _main()_ no arquivo main.c foi  modificada para fazer uma chamada a yyparse().

__Atenção: Colocar os nomes dos membros da equipe como comentário na primeira linha de main.c.__

## Compilação de ```bminus```

```$ bison -d bminus.y```
```$ cc -o bminus bminus.tab.c lex.yy.c main.c```

## Execução do analisador sintático ```bminus```

```$./bminus exemplo_0.bm exemplo_0.out``` 


O arquivo ```exemplo_0.bm``` contém um programa-fonte em B-.
Para T2, ```exemplo_0.out``` será criado porém vazio (0KB).
As mensagens de saída do analisador sintático são enviadas para ```stderr'''.
- Obs.: Em T2, o arquivo de saída é criado apenas para uso na correção automática de T2.


**Observação**:  Atenção para os nomes usados no T2.
- O nome do arquivo Bison deve ser bminus.y
- O nome do arquivo que contém a função _main_ deve ser main.c.

## Exemplos

### Exemplo 1 (sem erro sintático)

```
// exemplo sem erro sintatico

main: function integer () =
{
    a: integer;
    read(a);
    if (a <= 0) 
       a = 1;
    print(a);
}
```

- Saída após análise sintática do programa: um arquivo vazio (0KB)

### Exemplo 2 (*com* erro sintático)

```
// exemplo com erro sintatico

main: function integer () =
{
    x: integer;
    read(x);
    if (x != 0 
       x = 1;
    print(x);
}
```

- Saída após análise sintática do programa: um arquivo com apenas uma linha, contendo:

```erro sintático.```


## Correção Automática

A correção automática do trabalho T2 será feita com o apoio de _scripts_.
Desse modo, a correção irá considerar apenas os arquivos colocados 
no repositório GitHub da equipe,
com os nomes de arquivos indicados na especificação do trabalho.

