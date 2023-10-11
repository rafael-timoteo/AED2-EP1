/* Vértices de grafos são representados por objetos do tipo vertex. */

#define vertex int

/* A lista de adjacência de um vértice v é composta por nós do tipo node. Cada nó da lista corresponde a um arco 
e contém um vizinho w de v e o endereço do nó seguinte da lista. Um link é um ponteiro para um node. */

typedef struct node *link;

struct node { 
   vertex w; 
   link next; 
};

/* Um Graph é um ponteiro para um graph. */

typedef struct graph *Graph;

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A estrutura graph representa um grafo. O campo adj é um ponteiro 
para o vetor de listas de adjacência, o campo V contém o número de vértices e o campo A contém o número de arcos 
do grafo. */

struct graph {
   int V; 
   int A; 
   link *adj; 
};

Graph GRAPHinit(int V);
void GRAPHinsertArc( Graph G, vertex v, vertex w);
Graph GRAPHrandER(int V, int A);
static link NEWnode(vertex w, link next);
void ImprimeGrafo(Graph G, char ** palavras);
void GRAPHdestroy(Graph G);
int GRAPHstrongCompsK1( Graph G, int *sc);
int GRAPHstrongCompsK2( Graph G, int *sc);
static void dfsR( Graph G, vertex v);
Graph GRAPHreverse( Graph G);
static void dfsRstrongCompsK( Graph G, vertex v, int *sc, int k);
int GRAPHstrongCompsKreverso( Graph G, int *sc, int k);
void ImprimeGrafoRandom(Graph G);