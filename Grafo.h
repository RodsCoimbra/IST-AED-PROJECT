#ifndef Grafo_h
#define Grafo_h
#define max 2147483647
#include <stdio.h>

typedef struct lista_de_adjacencia
{
    struct lista_de_adjacencia *next;
    int no;
    int custo;
    unsigned short linha;
    unsigned short coluna;
} ladj;

typedef struct grafo
{
    ladj **list;
    int V; /*Vertices*/
} G;

G *Grafoini(int V);
ladj *adjacente(int custo, int no, ladj *list, int l, int c);
void Grafofree(G *g);
void encontra_caminho(G *g, int sala_do_tesouro, FILE *fsol);

#endif