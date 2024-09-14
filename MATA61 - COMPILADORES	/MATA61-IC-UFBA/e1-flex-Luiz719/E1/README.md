# Exercício E1 - Aquecimento com Flex

- Alterar calc.l para:

  - Criar um novo token, ERROR, para sinalizar erro léxico;
  - Mover mensagem de erro para a função main();
  - Alterar padrão regular de NUM para reconhecer números com até duas casas decimais (p.e. ```0.75'''; não aceitar ```.75''' ou ````0.751''').

- Incluir declaração do novo token: Editar calc.y e depois rodar ```bison -d calc.y''' antes de compilar.

- Rodar flex, bison, compilar e testar (assumir entrada padrão);

- Submeter sua resposta via GitHub.
