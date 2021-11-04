#ifndef Grafo_h
#define Grafo_h

typedef struct lista_de_adjacencia
{
    struct lista_de_adjacencia *next;
    int no;
    int custo;
} ladj;

typedef struct grafo
{
    ladj **list;
    int V; /*vertices*/
    int E; /*Arestas*/
} G;

G *Grafoini(int V);

#endif