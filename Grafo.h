#ifndef Grafo_h
#define Grafo_h
#define max -1
#include <stdio.h>

typedef struct lista_de_adjacencia
{
    struct lista_de_adjacencia *next;
    int no;
    int custo;
    int linha;
    int coluna;
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

ladj *adjacente(int custo, int no, ladj *list, int l, int c);

void Grafofree(G *g);

void encontra_caminho(G *g, int sala_do_tesouro, FILE *fsol);
void printfree(print *head);
print *printinsert(int linha, int custo, int coluna, print *head);

#endif