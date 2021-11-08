#ifndef Grafo_h
#define Grafo_h
#define max 2147483647
#include <stdio.h>

typedef struct lista_de_adjacencia
{
    struct lista_de_adjacencia *next;
    int no;
    int custo;
    short linha;
    short coluna;
} ladj;

typedef struct grafo
{
    ladj **list;
    int V; /*Vertices*/
} G;

typedef struct print
{
    struct print *next;
    int custo;
    short linha;
    short coluna;
} print;

G *Grafoini(int V);

ladj *adjacente(int custo, int no, ladj *list, short l, short c);

void Grafofree(G *g);

void encontra_caminho(G *g, int sala_do_tesouro, FILE *fsol);
void printfree(print *head);
print *printinsert(short linha, short coluna, int custo, print *head);

#endif