# B-Minus

A linguagem B- é uma linguagem “pequena” usada para o ensino de compiladores em cursos de graduação. 
B- inclui expressões, fluxo de controle básico, funções recursivas e 
verificação de tipos. O código-objeto é compatível com C e, portanto, 
algumas bibliotecas C padrão podem ser usadas para os tipos definidos na linguagem.

Descreveremos a linguagem através de exemplos, deixando para você ler com atenção, fazer perguntas no Fórum e então extrair as especificações formais necessárias para desenvolver os trabalhos do curso.

## Aspectos Léxicos

### 1. Caracteres de espacejamento (_whitespace_)

Os caracteres de espacejamento são _blank_ (' '), _newline_ ('\n'),  _tab_ ('\t') e _carriage return_ ('\r').

Os caracteres de espacejamento não têm papel significativo em programas B- e devem ser desconsiderados pelo analisador léxico.

### 2. Comentários de uma linha

Comentários de uma linha (_single-line comments_) sempre são iniciados por ```//``` e se estendem até o final da linha.
Comentários devem ser desconsiderados.

- Exemplo: ```a=5; // comentário no estilo C++```

### 3. Identificadores

Identificadores são usados como nomes de variáveis e funções. 
São compostos por letras maiúsculas e minúsculas, dígitos decimais e _underscores_.
Identificadores devem começar com uma letra e podem ter até 256 caracteres.
Caracteres maiúsculos e minúsculos em identificadores são diferenciados.

- Exemplo: ```i x9 x9_ my_str name4you  NomeCompleto```
- Exemplo: ```x9``` e ```X9``` são dois identificadores distintos.

### 4. Palavras-chave (_keywords_)

```
array  boolean  else  false  function  if
integer  print  return  true  void   while
``` 

As palavras-chave, sempre escritas em letras minúsculas, são reservadas 
e não podem ser usadas como identificadores. 

- Exemplo: ```integer``` é palavra reservada, porém  ```IntegeR``` não é.

Duas palavras reservadas representam tipos atômicos da linguagem:

```integer``` e   ```boolean ```.

A palavra reservada ```array``` é usada na declaração de arrays, único tipoestruturado da linguagem.

### 5. Símbolos especiais

#### Símbolos simples

```
  +  -  *  /  %  !  <  >  =  : ;  ,  (  )  [  ]  {  } 
```

#### Símbolos compostos

```
  <=  >=  ==  !=  &&  ||
```

### 6. Literais 

#### Tipo ```integer```

Uma constante inteira é uma sequência não-vazia de dígitos decimais.

#### Tipo ```boolean```

Há duas constantes válidas para o tipo ```boolean```: ```false``` e ```true```.

### 6. Erros Léxicos

- caractere inválido 

### Exemplos

```
x: integer;
y: integer = 123;
b: boolean = false;
```

```
x: integer = 65;
y: boolean = true;
if(x?y) ... etc. // caractere inválido
```

```
f: integer = 0;
if(f<100) ...  etc.
```

```
writenum: function void ( b: integer );
a: integer = 99;
writenum(a); 
```

```
b: array [2] boolean = {true,false};
x: integer = 0;
if(b[0]) x = x+1;     
```

```

main: function integer () = {
    i: integer = 10;
    while (i > 0) ... etc.  
}
```

## Aspectos Sintáticos

TBD.

## Aspectos Semânticos 

TBD.

<!--

#### Tipos

- O tipo ```integer``` define constantes representadas como ``signed 64 bit```.
- O tipo ```boolean``` possui dois valores literais: _true_ e _false_.

- Arrays são estáticos, isto é, são criados com tamanho fixo e memória reservada; o tamanho não pode ser modificado depois.

- Se um array for declarado, sem valores atribuídos, assume-se que o mesmo foi inicializado com zeros.

``` a: array [5] integer; ```

- Na declaração de um array de tamanho N, pode-se inicializar o array com um conjunto de valores.

``` a: array [5] integer = {1,2,3,4,5}; ```

- Se um array for declarado, sem valores atribuídos, assume-se que o mesmo foi inicializado com zeros.

#### Função main


Um programa completo deve ter uma função chamada de ```main``` que retorna um valor inteiro. 
A lista de parâmetros de _main_ pode ser vazia ou usar ```argc``` 
e ```argv``` como em programas C. 
-->

-----

### Créditos

Adaptado do material didático cedido pelo Prof. Vinicius Petrucci e 
do livro de D. Thain.

<!-- you must copy yytext before the lexer is called again if you need to preserve the token's string representation. -->
