/*********************************************************************/
/**	ACH2024 - Algoritmos e Estruturas de Dados 2                  **/                
/**   EACH-USP - Primeiro Semestre de 2023                          **/
/**   Turma 94 - Profa. Karina Valdivia Delgado                     **/
/**                                                                 **/
/**   Exercicio-Programa                                            **/
/**                                                                 **/
/**	  Nomes:                                      N°s USP:        **/
/**	  <Rafael Francisco de Freitas Timoteo>       <12924740>      **/
/**	  <Guilherme Augusto Arrabal de Souza>        <5642180>       **/
/**                                                                 **/
/*********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

#define TAM 1000

int ComparaVertice(char ** t, char * r, int vert){

   int a;
   int k = 1;

   for(a = 0; a < vert; a++){
      k = strcmp(t[a], r);
      if(k == 0){
         return a;
      }
   }

   return printf("Vertice nao existe");

}

int main(int argc, char *argv[]) {

   int z = 0;
   int i, j, a, n, we, numvertices, kosarayu, compforte, compfortereverso; 
   char texto[TAM];
   char linha[TAM];
   char w[TAM];
   char k[3];
   char * t;
   link p;
   Graph aux;     // grafo inicial
   Graph auxcfc;  //grafo das componentes fortemente conectadas

   if (argc>1) {                        //adicionamos o textotxt na variável "texto"
      FILE * file;
      file = fopen(argv[1], "r");

      if(file){
         char c = fgetc(file);
         for(i = 0; c != EOF; i++){
            texto[i] = c;
            c = fgetc(file);
         }      
      }
      fclose(file);
   }

   t = &texto[0];

   for(i = 0; t[i] != '\n'; i++){
      linha[i] = t[i];
   }

   numvertices = strtol(linha, NULL, 10);       //aqui identificaremos a quantidade de vértices da primeira linha do arquivo, que ficará armazenada em "numvertices"
   
   aux = GRAPHinit(numvertices);                   //aqui vamos inicializar o grafo com a quantidade de vértices que está em "numvertices"

   n = i;

   char ** v = (char**) malloc(sizeof(char*)*numvertices);

   for(int l = 0; l < numvertices; l++){          //nesse primeiro ciclo for, vamos identificar todos os vértices do
      v[l] = (char*) malloc(sizeof(char)*TAM);    //arquivo txt e associar cada string da entrada ao valor v do vértice
      i++;
      while(t[i] != ':'){
         v[l][z] = t[i];
         z++;
         i++;
      }
      v[l][z] = '\0';
      z = 0;
      while(t[i] != '\n'){
         i++;
      }
   }

   for(int l = 0; l < numvertices; l++){       //nesse segundo ciclo for, vamos correr o restante do texto e
      n++;                                     //identificar os vértices adjacentes daqueles outros vértices      
      while(t[n] != ':'){                      
         n++;
      }
      n++;
     while(t[n] != '\n'){
         while(t[n] != ';'){
            w[z] = t[n];
            z++;
            n++;
         }
         w[z] = '\0';
         we = ComparaVertice(v, w, numvertices);     
         GRAPHinsertArc(aux, l, we);                  //insere um arco entre dois vértices
         z = 0;
         n++;
     }
   }
  
   a = 0;
   for(i = 0; texto[i] != '\0'; i++){  //aqui extraímos do arquivo se devemos implementar a versão 1 ou 2 de Kosarayu
      if(t[i] == '\n') j++;         
      if(j == numvertices + 1){
         k[a] = texto[i];
         a++;
      } 
   }

   kosarayu = strtol(k, NULL, 10);     


   int *cfc = (int*) malloc(sizeof(int)*numvertices);  //cfc = componente fortemente conectado. É no vetor cfc que iremos colocar os rótulos que vão indicar os vértices que fazem parte de um mesmo componente fortemente conectado
                                                    
   if(kosarayu == 1){
      compforte = GRAPHstrongCompsK1(aux, cfc);  // verificando componentes fortemente conectados na versão 1
   }else{
      compforte = GRAPHstrongCompsK2(aux, cfc);  // verificando componentes fortemente conectados na versão 2
   }

   if(compforte == 1){                           //informa se o grafo é fortemente conectado (Sim ou Não da saída)
      printf("Sim\n");
   }else{
      printf("Nao\n");
   }

   printf("%d\n", compforte);          ////informa quantas componentes fortemente conectados o grafo possui (segunda linha da saída)

   compfortereverso = GRAPHstrongCompsKreverso( aux, cfc, compforte-1);  //traz os rótulos (cfc) em ordem crescente

   char ** vcfc = (char**) malloc(sizeof(char) * compforte);  //aqui agrupamos as strings relativas aos vértices de forma que todas fiquem juntas caso façam parte de um mesmo cfc
   
   for(i = 0; i < compforte; i++){
      vcfc[i] = (char*) malloc(sizeof(char) * TAM);
      vcfc[i][0] = '\0';
   }

   for(i = 0; i < numvertices; i++){
      vcfc[cfc[i]] = strcat(vcfc[cfc[i]], v[i]);
   }

   for(i = 0; i < compforte; i++){     //imprimindo os componentes fortemente conectados (linha 3 da saída)
      printf("%s ", vcfc[i]);
   }
   
   printf("\n");

   if(compforte == numvertices){
      ImprimeGrafo(aux, v);
      return 0;
   }

   auxcfc = GRAPHinit(compforte);      //inicializa o grafo dos cfc

   for(i = 0; i < numvertices; i++){      //insere os arcos dos vértices no grafo dos cfc
      for(p = aux->adj[i]; p != NULL; p = p->next){
         if(cfc[i] != cfc[p->w]) GRAPHinsertArc(auxcfc, cfc[i], cfc[p->w]);
      }
   }

   ImprimeGrafo(auxcfc, vcfc);      //imprime grafo dos cfc

   GRAPHdestroy(aux);
   GRAPHdestroy(auxcfc);

   return 0;
}