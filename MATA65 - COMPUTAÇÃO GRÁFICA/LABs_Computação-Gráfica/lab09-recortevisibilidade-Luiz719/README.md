[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-2e0aaae1b6195c2367325f4f02e2d04e9abb55f0b24a779b69b11b9e10269abc.svg)](https://classroom.github.com/online_ide?assignment_repo_id=15410878&assignment_repo_type=AssignmentRepo)
# Lab09 - Algoritmos de Recorte e Visibilidade

## Objetivos:

1. Entender o problema de visibilidade no contexto de aplicações de visualização 3D;
2. Compreender as principais estratégicas utilizadas para resolver a visibilidade;
3. Controlar o processo de recorte, além do *frustum* da camera;
3. Experimentar os mecanismos de controle desses algoritmos providos pelos *framework Three.JS*;

## Exercícios:

1. Os artefatos que vemos na aplicação do algoritmo de *z-buffer* podem ser mitigados por uma técnica denominada *logarithmic depth buffer*. Pesquise seu funcionamento e disponibilidade no *Three.JS* e acrescente a opção na interface de ligar ou desligar essa funcionalidade para eliminar os artefatos presentes no exemplo. 

2. É possível criar outros planos de recorte além daqueles gerados pela *frustum* da camera. Pesquise como o *Three.JS* suporta esse planos adicionais e crie dois planos de recorte verticais (perpediculares ao plano da cidade), cuja posição seja controlada via *gui*.

## Referências:

- MARSCHNER, Steve; SHIRLEY, Peter. "**Fundamentals of Computer Graphics**". 5<sup>th</sup> Edition CRC Press, 2021.

- Dirksen, J., **Learn Three.JS: Program 3D animations and visualizations for the web with JavaScript and WebGL**. 4<sup>th</sup> Edition, Packt Publishing, 2023.

- https://threejs.org/docs/index.html

