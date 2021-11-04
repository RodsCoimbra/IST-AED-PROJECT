/*bibliotecas do projeto*/
#include "As.h"
#include "Funcoes_aux.h"
#include "Ficheiros_dados.h"
#include "Grafo.h"
/*bibliotecas*/
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
/*
typedef struct lista_de_adjacencia
{
    struct lista_de_adjacencia *next;
    int no;
    int custo;
} ladj;

typedef struct grafo
{
    ladj **list;
    int V;
    int E;
} G;
*/
G *Grafoini(int vertices)
{
    G *g = (G *)malloc(sizeof(G));
    if (g == NULL)
    {
        return NULL;
    }
    g->V = vertices;
    g->E = 0;
    g->list = (ladj **)malloc(sizeof(ladj *) * vertices);
}