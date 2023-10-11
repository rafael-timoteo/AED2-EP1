#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

static int cnt, pre[1000];
static int cntt, post[1000];
static vertex vv[1000];

/*A função GRAPHdestroy() recebe um ponteiro para uma estrutura Graph que 
representa o grafo a ser destruído.*/

void GRAPHdestroy(Graph G) {
   int v;
   for (v = 0; v < G->V; v++) {
      link t, p = G->adj[v];
      while (p != NULL) {
         t = p->next;
         free(p);
         p = t;
      }
   }
   free(G->adj);
   free(G);
}

/* Esta função atribui um rótulo sc[v] (os rótulos são 0,1,2,...) a cada vértice v do grafo G de modo que dois 
vértices tenham o mesmo rótulo se e somente se os dois pertencem à mesma componente forte. 
A função devolve o número (quantidade) de componentes fortes de G. (A função implementa o algoritmo de Kosaraju. 
O código é adaptado do Programa 19.10 de Sedgewick.) */

int GRAPHstrongCompsK1( Graph G, int *sc) 
{
   // fase 1:
   Graph GR = GRAPHreverse( G);
   cnt = cntt = 0;
   vertex v; 
   for (v = 0; v < GR->V; ++v) pre[v] = -1;
   for (v = 0; v < GR->V; ++v) 
      if (pre[v] == -1)
         dfsR( GR, v); 
   for (v = 0; v < GR->V; ++v) 
      vv[post[v]] = v;
   // vv[0..V-1] é permutação de GR em pós-ordem

   // fase 2:
   for (v = 0; v < G->V; ++v) sc[v] = -1;
   int k = 0;
   for (int i = G->V-1; i >= 0; --i) {
      v = vv[i];
      if (sc[v] == -1) { // nova etapa
         dfsRstrongCompsK( G, v, sc, k);
         k++;
      }
   }
   GRAPHdestroy( GR);
   return k;
}

/* Esta função atribui um rótulo sc[v] (os rótulos são 0,1,2,...) a cada vértice v do grafo G de modo que dois 
vértices tenham o mesmo rótulo se e somente se os dois pertencem à mesma componente forte. 
A função devolve o número (quantidade) de componentes fortes de G. (A função implementa o algoritmo de Kosaraju. 
O código é adaptado do Programa 19.10 de Sedgewick.) */

int GRAPHstrongCompsK2( Graph G, int *sc) 
{
   // fase 1:
   cnt = cntt = 0;
   vertex v;
   for (v = 0; v < G->V; ++v) pre[v] = -1;
   for (v = 0; v < G->V; ++v) 
      if (pre[v] == -1)
         dfsR( G, v); 
   for (v = 0; v < G->V; ++v) 
      vv[post[v]] = v;

   Graph GR = GRAPHreverse( G);

   // fase 2:
   for (v = 0; v < GR->V; ++v) sc[v] = -1;
   int k = 0;
   for (int i = GR->V-1; i >= 0; --i) {
      v = vv[i];
      if (sc[v] == -1) { // nova etapa
         dfsRstrongCompsK( GR, v, sc, k);
         k++;
      }
   }

   GRAPHdestroy( GR);
   return k;
}

/* Armazena no vetor post[] uma numeração em pós-ordem do grafo GR. O vetor pre[] marca os vértices já 
descobertos. */

static void dfsR( Graph GR, vertex v) 
{ 
   pre[v] = cnt++; 
   for (link a = GR->adj[v]; a != NULL; a = a->next)
      if (pre[a->w] == -1) 
         dfsR( GR, a->w); 
   post[v] = cntt++;
}

/* Constrói o reverso do grafo G. */

Graph GRAPHreverse( Graph G) 
{
   Graph GR = GRAPHinit( G->V);
   for (vertex v = 0; v < G->V; ++v) 
      for (link a = G->adj[v]; a != NULL; a = a->next)
         GRAPHinsertArc( GR, a->w, v);
   return GR;
}

/* Atribui o rótulo k a todo vértice w ao alcance de v que ainda não foi rotulado. Os rótulos são armazenados 
no vetor sc[]. */

static void dfsRstrongCompsK( Graph G, vertex v, int *sc, int k) 
{ 
   sc[v] = k;
   for (link a = G->adj[v]; a != NULL; a = a->next)
      if (sc[a->w] == -1) 
         dfsRstrongCompsK( G, a->w, sc, k);
}

/* É o mesmo código que busca as componentes fortemente conectadas, porém incluimos o parâmetro k, para que 
seja devolvido os rótulos em orden crescente de valor */

int GRAPHstrongCompsKreverso( Graph G, int *sc, int k){
   // fase 1:
   Graph GR = GRAPHreverse( G);
   cnt = cntt = 0;
   vertex v; 
   for (v = 0; v < GR->V; ++v) pre[v] = -1;
   for (v = 0; v < GR->V; ++v) 
      if (pre[v] == -1)
         dfsR( GR, v); 
   for (v = 0; v < GR->V; ++v) 
      vv[post[v]] = v;
   // vv[0..V-1] é permutação de GR em pós-ordem

   // fase 2:
   for (v = 0; v < G->V; ++v) sc[v] = -1;
   for (int i = G->V-1; i >= 0; --i) {
      v = vv[i];
      if (sc[v] == -1) { // nova etapa
         dfsRstrongCompsK( G, v, sc, k);
         k--;
      }
   }
   GRAPHdestroy( GR);
   return k;
}


/*A função ImprimeGrafo imprime o grafo*/

void ImprimeGrafo(Graph G, char ** palavra) {
   int i;
   link p;

   for(i = 0; i < G->V; i++){
      printf("%s: ", palavra[i]);
      for(p = G->adj[i]; p != NULL; p = p->next){
         printf("%s; ", palavra[p->w]);
      }
      printf("\n");
   }
}

/*Imprime grafo aleatório*/

void ImprimeGrafoRandom(Graph G){
   int i;
   link p;

   for(i = 0; i < G->V; i++){
      printf("%d: ", i);
      for(p = G->adj[i]; p != NULL; p = p->next){
         printf("%d; ", p->w);
      }
      printf("\n");
   }
}


/* A função NEWnode() recebe um vértice w e o endereço next de um nó e devolve o endereço a de um novo nó 
tal que a->w == w e a->next == next. */

static link NEWnode( vertex w, link next) { 
   link a = malloc( sizeof (struct node));
   a->w = w; 
   a->next = next;     
   return a;                         
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função GRAPHinsertArc() insere um arco v-w no grafo G. 
A função supõe que v e w são distintos, positivos e menores que G->V. Se o grafo já tem um arco v-w, 
a função não faz nada. */

void GRAPHinsertArc( Graph G, vertex v, vertex w) { 
   for (link a = G->adj[v]; a != NULL; a = a->next) 
      if (a->w == w) return;
   G->adj[v] = NEWnode( w, G->adj[v]);
   G->A++;
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função GRAPHinit() constrói um grafo com vértices 0 1 .. V-1 e 
nenhum arco. */
Graph GRAPHinit( int V) { 
   Graph G = malloc( sizeof *G);
   G->V = V; 
   G->A = 0;
   G->adj = malloc( V * sizeof (link));
   for (vertex v = 0; v < V; ++v) 
      G->adj[v] = NULL;
   return G;
}

/* Constrói um grafo aleatório com vértices 0..V-1 e número esperado de arcos igual a A. 
A função supõe que V >= 2 e A <= V*(V-1). (Código inspirado no Program 17.8 de Sedgewick.) */

Graph GRAPHrandER(int V, int A) { 
   double prob = (double) A / (V*(V-1));
   Graph G = GRAPHinit( V);
   for (vertex v = 0; v < V; ++v)
      for (vertex w = 0; w < V; ++w)
         if (v != w)
            if (rand( ) < prob*(RAND_MAX+1.0))
               GRAPHinsertArc( G, v, w);
   return G;
}
