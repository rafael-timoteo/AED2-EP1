#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "grafo.h"

#define V 30
#define A 500
#define kosarayu 2

int main(){

Graph auxrandom;
Graph aux;
int i, j, compforte, compfortereverso;
int *cfc = (int*) malloc(sizeof(int)*V);             //cfc = componente fortemente conectado
link p;

auxrandom = GRAPHrandER(V,A);

   ImprimeGrafoRandom(auxrandom);

   if(kosarayu == 1){
      compforte = GRAPHstrongCompsK1(auxrandom, cfc);  // verificando componentes fortemente conectados na versão 1
    }
   else{
      compforte = GRAPHstrongCompsK2(auxrandom, cfc);  // verificando componentes fortemente conectados na versão 2
    }

   if(compforte == 1){
      printf("Sim\n");
   }else{
      printf("Nao\n");
   }

   printf("%d\n", compforte);

   compfortereverso = GRAPHstrongCompsKreverso(auxrandom, cfc, compforte-1);

   for(i = 0; i < V; i++){
      for(j = 0; j < V; j++){
         if(cfc[j] == i) printf("%d", j);
      }
      printf("  ");
   }

   printf("\n"); 
 
   aux = GRAPHinit(compforte);

   for(i = 0; i < V; i++){
      for(p = auxrandom->adj[i]; p != NULL; p = p->next){
         if(cfc[i] != cfc[p->w]) GRAPHinsertArc(aux, i, p->w);
      }
   }

   ImprimeGrafoRandom(aux);

   return 0;
}