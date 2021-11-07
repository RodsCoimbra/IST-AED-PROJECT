/*bibliotecas do projeto*/
#include "As.h"
#include "Funcoes_aux.h"
#include "Ficheiros_dados.h"
#include "Grafo.h"
#include "Fila.h"
/*bibliotecas*/
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

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
    if (g->list == NULL)
    {
        return NULL;
    }
    return g;
}
/**
 * @brief
 *
 * @param custo
 * @param no
 * @param list
 * @param l
 * @param c
 * @return ladj* Se retornar NULL quer dizer erro, não esquecer no código principal
 */
ladj *adjacente(int custo, int no, ladj *list, int l, int c)
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
            novo->linha = l;
            novo->coluna = c;
        }
        else
        {
            if (aux2->next->custo > custo)
            {
                aux2->next->custo = custo;
                aux2->next->linha = l;
                aux2->next->coluna = c;
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
        novo->linha = l;
        novo->coluna = c;
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

// Baseado no algoritmo do Dijkstra dos acetatos
void encontra_caminho(G *g, int sala_do_tesouro, FILE *fsol)
{
    Filaini(g->V);
    int vertice;
    int *origem = (int *)malloc(g->V * sizeof(int)), *pesos = (int *)malloc(g->V * sizeof(int));
    if (origem == NULL || pesos == NULL)
    {
        exit(0);
    }
    for (int i = 0; i < g->V; i++)
    {
        origem[i] = max;
        pesos[i] = max;
    }

    Filainsert(0, 0);
    pesos[0] = 0;
    origem[0] = 0;
    while (Free != 0)
    {
        vertice = Proximo_na_fila();
        if (vertice == sala_do_tesouro)
        {
            continue;
        }
        for (ladj *aux = g->list[vertice]; aux != NULL; aux = aux->next)
        { // Para depois testar no if(pesos[sala_do_tesouro] == -1 || pesos[sala_do_tesouro] <)
            if ((pesos[aux->no] > (pesos[vertice] + aux->custo) || pesos[aux->no] == -1))
            {
                Filainsert(aux->no, aux->custo);
                pesos[aux->no] = pesos[vertice] + aux->custo;
                origem[aux->no] = vertice;
            }
        }
    }
    ladj *aux;
    int k = 0;
    print *pr = NULL;
    fprintf(fsol, "%d\n", pesos[sala_do_tesouro]);
    free(pesos);
    for (int i = sala_do_tesouro; i != 0; i = origem[i])
    {
        for (aux = g->list[i]; (aux != NULL && aux->no != origem[i]); aux = aux->next)
            ;
        k++;
        pr = printinsert(aux->linha, aux->coluna, aux->custo, pr);
    }
    fprintf(fsol, "%d\n", k);
    for (print *aux = pr; aux != NULL; aux = aux->next)
    {
        fprintf(fsol, "%d %d %d\n", aux->linha, aux->coluna, aux->custo);
    }
    printfree(pr);
    free(origem);
}

print *printinsert(int linha, int coluna, int custo, print *head)
{
    print *novo = (print *)malloc(sizeof(print));
    if (novo == NULL)
    {
        exit(0);
    }
    novo->next = head;
    novo->linha = linha;
    novo->custo = custo;
    novo->coluna = coluna;
    return novo;
}

void printfree(print *head)
{
    for (print *aux = head, *aux2; aux != NULL; aux = aux2)
    {
        aux2 = aux->next;
        free(aux);
    }
}