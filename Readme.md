# Project Name
Projeto gráfico, Sistema Solar

## Commands for interaction
> Tecla s: Esonder ou mostrar sol
> Tecla m: Esonder ou mostrar Mercúrio
> Tecla v: Esonder ou mostrar Vênus
> Tecla t: Esonder ou mostrar Terra
> Tecla M: Esonder ou mostrar Marte
> Tecla j: Esonder  ou mostrar Júpter
> Tecla S: Esonder  ou mostrar Saturno
> Tecla u: Esonder  ou mostrar Urano
> Tecla n: Esonder  ou mostrar Neturno

> Tecla 1: Esonder  ou mostrar órbita 1
> Tecla 2: Esonder  ou mostrar órbita 2
> Tecla 3: Esonder  ou mostrar órbita 3
> Tecla 4: Esonder  ou mostrar órbita 4
> Tecla 5: Esonder  ou mostrar órbita 5
> Tecla 6: Esonder  ou mostrar órbita 6
> Tecla 7: Esonder  ou mostrar órbita 7
> Tecla 8: Esonder  ou mostrar órbita 8

> Tecla e: Executa ou pausa animação
> Tecla z: Enconder ou mostrar dados da terra

## Explanation
O projeto tem a função "Desenha" como função principal, ela é responsável por articular todas as outras funções auxiliares para realizar toda a construção do nosso cenário. Partindo desse princípio, agora iremos descrever cada uma dessas funções auxiliares a seguir.

Para realizar o desenho do Sol e de todos os planetas que está presente no sitema solar criamos uma função chamada "desenhaPlaneta". Esta função recebe 4 parametros, sendo eles, diametro do objeto em questão (número inteiro), cor (array de double), quantidade de órbitas (número inteiro) e quantidade de satelites (número inteiro), respectivamente.

Quando a chamada da função "desenhaPlaneta" é realizada, a mesma é responsável por fazer o desenho geométrico em questão que pode representar o sol ou os planetas que compõe o sistema solar. A função "desenhaPlaneta" também é encarregada de realizar a chamada da função "desenhaOrbita", que está localizada dentro de uma estrutura de repetição que realiza n chamadas da função "desenhaOrbita", que recebe como parâmetro o raio da órbita (número double). Logo após o desenho de todas as órbitas serem realizadas. A função "desenhaPlaneta" irá agora chamar a função "desenhaSatelite" que também se encontra dentro de uma estrutura de repetição que realiza n chamadas da função "desenhaSatelite", recebendo como parâmetro a distância em que o satélite se encontra do planeta em questao (número double).

Para realizar o comando de ocultar um determinado planeta ou órbita, foi criado a função "GerenciaTeclado", onde o mesmo recebe como parametro um char que representa a letra inicial de um determinado planeta do sistema solar. Essa letra irá cair em uma estrutura condicional que irá analisar qual planeta queremos ocultar, invertendo a variável de exibição que representa tal planeta para "false". Quando essa conversão é realizada, nossa função principal "Desenha" passa a não exibir o planeta em questão.