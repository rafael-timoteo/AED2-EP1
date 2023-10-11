# AED2-EP1
Primeiro trabalho de exercício programa para a matéria Algoritmos e Estrutura de Dados 2

Nomes: Rafael Francisco de Freitas Timoteo. N° USP: 12924740 
Guilherme Augusto Arrabal de Souza. N° USP: 5642180 
/******************************************************************
***********************************************************/
Este programa possui 4 códigos fonte: grafoep.c, que contém a 
função main e que irá gerar as quatro primeiras saídas que constam 
na especificação do EP mais a saída da aplicação prática; 
grafoaleatorio.c, que contém a função main e que irá gerar a saída 
do grafo aleatório; grafo.h, que contém as estruturas utilizadas 
para inicializar o grafo e criar a lista de adjacências e os 
protótipos das funções principais que irão manipular os grafos; 
grafo.c, que contém as funções declaradas em grafo.h que irão 
inicializar e manipular os grafos. Além dos códigos fonte, temos 
também as quatro entradas em formato txt, que estão escritas 
conforme as especificações do ep e às quais demos os seguintes 
nomes: grafoa.txt, grafob.txt, grafoc.txt, grafod.txt e grafoe.txt. 
Os quatro primeiros arquivos txt são aqueles referentes às quatro 
primeiras entradas especificadas no ep, respectivamente. O arquivo 
grafo.e é referente ao exemplo da aplicação prática dos grafos 
fortemente conectados.
/******************************************************************
***********************************************************/
Antes de efetuar a compilação, coloque todos os arquivos citados 
acima em uma mesma pasta.
Para compilar o código fonte grafoep.c: abra o prompt de comando ou 
o terminal do Linux e digite "gcc grafoep.c grafo.c -o grafoep.exe" 
na linha de comando do prompt de comando ou no terminal do linux.
Para executar: depois de compilado, digite: grafoep 
“arquivotexto.txt”.
Exemplos de como executar: 
grafoep grafoa.txt >> irá gerar a primeira saída conforme a 
especificação do ep.
grafoep grafob.txt >> irá gerar a segunda saída conforme a 
especificação do ep.
grafoep grafoc.txt >> irá gerar a terceira saída conforme a 
especificação do ep.
grafoep grafod.txt >> irá gerar a quarta saída conforme a 
especificação do ep.
grafoep grafoe.txt >> irá gerar a saída da aplicação prática, 
conforme a especificação do ep.
