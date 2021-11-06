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
ladj *adjacente(int custo, int no, ladj *list)
{
    ladj *novo, *aux2, aux;
    aux.next = list;
    if (list != NULL)
    {
        for (aux2 = &aux; aux2->next != NULL && aux2->next->no < no; aux2 = aux2->next)
            ;
        if (aux2->next == NULL || aux2->next->no != no)
        {
            novo = (ladj *)malloc(sizeof(ladj));
            // printf("\n%p", novo);
            if (novo == NULL)
            {
                return NULL;
            }
            novo->next = aux2->next;
            aux2->next = novo;
            novo->no = no;
            novo->custo = custo;
        }
        else
        {
            if (aux2->next->custo > custo)
            {
                aux2->next->custo = custo;
            }
            else
            {
                return NULL + 1;
            }
        }
        return aux.next;
    }
    else
    {
        novo = (ladj *)malloc(sizeof(ladj));
        if (novo == NULL)
        {
            return NULL;
        }
        novo->no = no;
        novo->next = NULL;
        novo->custo = custo;
        return novo;
    }
}

void Grafofree(G *g)
{
    for (int i = 0; i < (g->V); i++)
    {
        for (ladj *aux = g->list[i], *aux2; aux != NULL; aux = aux2)
        {
            aux2 = aux->next;
            free(aux);
        }
    }
    free(g->list);
    free(g);
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