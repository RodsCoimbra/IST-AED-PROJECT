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
 * @brief Inicializa o grafo com todas as suas variáveis
 *
 * @param vertices: Quantidade de salas diferentes no tabuleiro
 * @return G*: Se retornar NULL quer dizer erro, se não retorna um pointer da struct grafo
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
 * @brief Aloca um espaço na lista de adjacencia para uma sala caso esta ainda não exista e coloca lá os dados, senão
 * percorre a lista para colocar o novo nó adjacente aquela sala de forma a deixar a lista ordenada por nós. Caso já exista
 * aquele nó em especifico para aquela sala ele simplesmente substitui os dados pelos novos
 *
 * @param custo: custo da parede que separa as duas salas
 * @param no: nó a que se quer ligar aquela sala
 * @param list: lista daquela sala
 * @param l: linha da parede
 * @param c: coluna da parede
 * @return ladj*: Se retornar NULL quer dizer que o custo da nova parede era maior, senão retorna aux->next que é a head da lista
 */
ladj *adjacente(int custo, int no, ladj *list, int l, int c)
{
    ladj *novo, *aux2, aux;
    aux.next = list; // Cria-se uma struct antes que apontará para a antiga(porque pode ser mudada) head da lista
    if (list != NULL)
    {
        for (aux2 = &aux; aux2->next != NULL && aux2->next->no < no; aux2 = aux2->next)
            ;
        // percorre a lista até aux2->next ser null ou até o nó do aux2->next ser maior ou igual que o no passado na função
        if (aux2->next == NULL && aux2->no == no)
        // caso o aux2 seja o último elemento da lista
        {
            if (aux2->custo >= custo)
            {
                aux2->custo = custo;
                aux2->linha = l;
                aux2->coluna = c;
            }
            else // caso o custo seja maior ou igual ao que já lá estava não se substitui nada e retorna NULL
            {
                return NULL;
            }
        }
        else if (aux2->next == NULL || aux2->next->no != no)
        // caso seja NULL ou não encontrou um nó igual ao atual quer dizer que precisa de alocar espaço para esse novo nó
        {
            novo = (ladj *)malloc(sizeof(ladj));
            if (novo == NULL)
            {
                exit(0);
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
            if (aux2->next->custo >= custo)
            {
                aux2->next->custo = custo;
                aux2->next->linha = l;
                aux2->next->coluna = c;
            }
            else // caso o custo seja maior ou igual ao que já lá estava não se substitui nada e retorna NULL
            {
                return NULL;
            }
        }
        return aux.next; // retorna a head da lista
    }
    else // caso a lista para aquele sala não tenha sido criada ainda então cria
    {
        novo = (ladj *)malloc(sizeof(ladj));
        if (novo == NULL)
        {
            exit(0);
        }
        novo->no = no;
        novo->next = NULL;
        novo->custo = custo;
        novo->linha = l;
        novo->coluna = c;
        return novo;
    }
}

/**
 * @brief Dá free do grafo
 *
 * @param g: Grafo que se vai dar free
 */
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

/**
 * @brief Algoritmo do Dijkstra, que serve para encontrar o caminho mais barato
 * da sala 0(sala que contém a célula 1,1) até à sala do tesouro
 *
 * @param g: Grafo com toda a informação das arestas mais baratos
 * @param sala_do_tesouro: Sala onde se encontra a célula que se chegar
 * @param fsol: ficheiro de saida com a solução
 */
// Baseado no algoritmo do Dijkstra dos acetatos
void encontra_caminho(G *g, int sala_do_tesouro, FILE *fsol)
{
    int tamanho = 0, Free = 0;
    int *posicao = (int *)malloc(g->V * sizeof(int));
    int **fila = Filaini(g->V, posicao, &tamanho);
    int vertice;
    int *origem = (int *)malloc(g->V * sizeof(int)), *pesos = (int *)malloc(g->V * sizeof(int));
    if (origem == NULL || pesos == NULL)
    {
        exit(0);
    }
    for (int i = 0; i < g->V; i++)
    {
        origem[i] = -1;
        pesos[i] = max;
    }

    Filainsert(sala_do_tesouro, 0, fila, posicao, &Free);
    pesos[sala_do_tesouro] = 0;
    origem[sala_do_tesouro] = sala_do_tesouro;
    while (Free != 0)
    {
        vertice = Proximo_na_fila(fila, posicao, &Free);
        if (vertice == 0)
        {
            continue;
        }
        // percorre-se a lista do vértice de maior prioridade
        for (ladj *aux = g->list[vertice]; aux != NULL; aux = aux->next)
        { // vê se o peso novo é menor que o guardado anteriormente(max se nunca se foi aquela sala) e que o da sala do tesouro(max se ainda não chegou lá)
            if ((pesos[aux->no] > (pesos[vertice] + aux->custo)) && ((pesos[vertice] + aux->custo) < pesos[0]))
            {
                pesos[aux->no] = pesos[vertice] + aux->custo;
                Filainsert(aux->no, pesos[aux->no], fila, posicao, &Free);
                origem[aux->no] = vertice; // origem é a sala que se usou para chegar aquele nó
            }
        }
    }
    freefila(fila, posicao, &tamanho);
    ladj *aux;
    int k = 0;
    if (pesos[0] == max) // se o peso for igual a max quer dizer que nunca se chegou lá, logo a resposta será -1
    {
        fprintf(fsol, "-1\n");
        free(pesos);
        free(origem);
        return;
    }
    fprintf(fsol, "%d\n", pesos[0]);
    free(pesos);
    for (int i = 0; i != sala_do_tesouro; i = origem[i]) // percorre-se a origem do fim para o inicio(dos usados no algoritmo, porque tecnicamente é a ordem certa) e guarda-se a linha, a coluna e o custo das paredes numa lista
    {
        k++;
    }
    fprintf(fsol, "%d\n", k);
    for (int i = 0; i != sala_do_tesouro; i = origem[i]) // percorre-se a origem do fim para o inicio(dos usados no algoritmo, porque tecnicamente é a ordem certa) e guarda-se a linha, a coluna e o custo das paredes numa lista
    {
        for (aux = g->list[i]; (aux != NULL && aux->no != origem[i]); aux = aux->next) // Percorre a lista até ao nó que queremos para imprimir o custo e as coordenadas da parede
            ;
        fprintf(fsol, "%d %d %d\n", aux->linha, aux->coluna, aux->custo);
    }
    free(origem);
}
