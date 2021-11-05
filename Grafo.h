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
    int V; /*Vertices*/
    int E; /*Arestas*/
} G;

G *Grafoini(int V);

ladj *adjacente(int custo, int no, ladj *list);

void Grafofree(G* g);

#endif