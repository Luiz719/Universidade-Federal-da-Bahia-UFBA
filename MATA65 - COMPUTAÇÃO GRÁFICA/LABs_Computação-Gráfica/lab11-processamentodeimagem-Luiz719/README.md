[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/aaWz_-u6)
# Lab 11 - Processamento de Imagem em *Three.JS*

## Objetivos:

1. Compreender o conceito de processamento de imagens dentro do framework *Three.JS*;
2. Aplicar transformações de Intensidade em imagens com *shaders*.
3. Utilizar filtros espaciais para processar imagens usando *shaders* e texturas.

# Atividades Pontuadas:

1. Altere o exemplo *01-procImagem* para mostrar a imagem *lena.png* com seus 3 canais de cor separados. Utilize o conceito de *viewport* [1] para dividir a tela em 4 regiões para mostrar a imagem original e os canais de cor.

2. Altere o exercicio anterior para mostrar a imagem *lena.png* com seus 3 canais de cor porém agora representados no sistema HSL[4]. Mostre a imagem original e os 3 canais de cor HSL.

3. Faça um programa que aplique a **transformação de binarização** na imagem *lena.png*. O valor do limiar deve ser selecionado via *GUI*.

4. Crie um programa que aplique a **transformação negativa** na imagem *lena.png*. A transformação pode ser aplicada em cada canal de cor da image e a seleção do canal a ser invertido será feita via *GUI*. Considere que as transformações podem ser combinadas. 

5. Faça um programa que aplique as **transformações log e gama** nos canais de cor da imagem *lena.png*. A seleção da transformação bem como sua intensidade devem ser selecionadas via *GUI* do programa. As transformações devem ser mutuamente excludentes.  

6. Modifique o exercício anterior para que as transformações sejam aplicadas apenas no canal de luminosidade da imagem (considerando sua representação em HSL produzida no exercício 2). Após a transformação o valor do pixel deve ser convertido novamente para a representação RGB [4] para ser apresentado.  

## Referências:

[1] MARSCHNER, Steve; SHIRLEY, Peter. "**Fundamentals of Computer Graphics**". 5th Edition CRC Press, 2021.

[2] Dirksen, J., **Learn Three.JS: Program 3D animations and visualizations for the web with JavaScript and WebGL**. 4th Edition, Packt Publishing, 2023.

[3] Three.js Docs, https://threejs.org/docs/index.html

[4]	HSL to RGB to HSL, https://www.shadertoy.com/view/XljGzV
