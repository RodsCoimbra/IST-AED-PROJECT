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

/**
 * @brief
 *
 * @param vertices
 * @return G* Se retornar NULL quer dizer erro, não esquecer no código principal
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
    g->list = (ladj **)calloc(1, sizeof(ladj *) * vertices);
    return g;
}
/**
 * @brief
 *
 * @param custo
 * @param no
 * @param g
 * @return ladj* Se retornar NULL quer dizer erro, não esquecer no código principal
 */
ladj *adjacente(int custo, int no, ladj *g)
{
    ladj *novo = g, *aux, *aux2, aux3;
    aux = &aux3;
    aux->next = g;
    novo = (ladj *)malloc(sizeof(ladj));
    if (novo == NULL)
    {
        return NULL;
    }
    if (g != NULL)
    {
        for (aux2 = aux; aux2->next != NULL && aux2->next->custo <= custo; aux2 = aux2->next)
            ;

        novo->next = aux2->next;
        aux2->next = novo;
        novo->no = no;
        novo->custo = custo;
        return aux->next;
    }
    else
    {
        novo->no = no;
        novo->next = NULL;
        novo->custo = custo;
        return novo;
    }
}

/* Código para testar adjacente
    G *g;
    ladj *aux;
    g = Grafoini(4);
    if (g == NULL)
    {
        exit(0);
    }
    g->list[0] = adjacente(3, 1, g->list[0]);
    g->list[1] = adjacente(3, 0, g->list[1]);
    g->list[0] = adjacente(1, 2, g->list[0]);
    g->list[2] = adjacente(1, 0, g->list[2]);
    g->list[0] = adjacente(2, 3, g->list[0]);
    g->list[3] = adjacente(2, 0, g->list[3]);
    g->list[2] = adjacente(1, 3, g->list[2]);
    g->list[3] = adjacente(1, 2, g->list[3]);
    for (int i = 0; i < (g->V); i++)
    {
        for (aux = g->list[i]; aux != NULL; aux = aux->next)
        {
            printf("%d:%d ", aux->no, aux->custo);
        }
        printf("-1\n");
    }

    exit(0);*/