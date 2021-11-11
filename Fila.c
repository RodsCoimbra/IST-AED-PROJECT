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
#define troca_fila(a, b) \
    {                    \
        int *aux;        \
        aux = a;         \
        a = b;           \
        b = aux;         \
    }
#define troca_posicoes(a, b) \
    {                        \
        int aux;             \
        aux = a;             \
        a = b;               \
        b = aux;             \
    }

/**
 * @brief Inicia uma fila de acervos
 *
 * @param vertices:numero de vertices do grafo
 *
 \return void
 */
void Filaini(int vertices)
{
    fila = (int **)malloc(vertices * sizeof(int *));
    posicao = (int *)malloc(vertices * sizeof(int));
    if (fila == NULL || posicao == NULL)
    {
        exit(0);
    }
    for (int i = 0; i < vertices; i++)
    {
        fila[i] = (int *)malloc(2 * sizeof(int));
        if (fila[i] == NULL)
        {
            exit(0);
        }
        fila[i][0] = -1;
        fila[i][1] = 0;
        posicao[i] = -1;
        tamanho = vertices;
        Free = 0; /*Total de nós no grafo existentes */
    }
}

/**
 * @brief
 *
 * @param no: Nó do grafo que se quer inserir
 * @param custo: Custo do nó que se quer inserir
 *
 \return void
 */
void Filainsert(int no, int custo)
{
    if (posicao[no] == -1) /* Caso ainda não esteja na fila */
    {
        fila[Free][0] = no;
        fila[Free][1] = custo;
        posicao[no] = Free;
        Fixup(Free); /* Coloca o nó que está na posição "Free" da lista na posição correta do acervo segunda a ordem de prioridades */
        Free++;
    }
    else
    {
        fila[posicao[no]][1] = custo;
        Fixup(posicao[no]); /* Coloca o nó que está na posição posicao[no] da lista na posição correta do acervo segunda a ordem de prioridades */
    }
}

/**
 * @brief Com o nó passado como argumento, a função eleva-o até este estar na posição correta do acervo segundo a ordem de prioridades
 *
 * @param Free: número total de nós na fila
 *
 \return void
 */
void Fixup(int Free)
{
    for (int livre = Free; livre > 0 && fila[(livre - 1) / 2][1] > fila[livre][1]; livre = (livre - 1) / 2)
    {
        troca_fila(fila[livre], fila[(livre - 1) / 2]);
        troca_posicoes(posicao[fila[livre][0]], posicao[fila[(livre - 1) / 2][0]]);
    }
}

/**
 * @brief A função verifica se o primeiro elemento está bem posicionado e se não acontecer fá-lo descer na fila até à posição correta do acervo, respeitando a ordem de prioridades
 *
 *
 \return void
 */
void FixDown()
{
    int N = Free - 1, child, pai = 0;
    while ((pai * 2) < N)
    {
        child = (pai * 2) + 1;                                 /* O pai está sempre na posição (N-1)/2 em relação ao filho sendo N a posição do filho */
        if (child == N || fila[child][1] < fila[child + 1][1]) // Se o filho for igual a N,ou seja, só existe um filho, ou o filho é menor que o filho + 1, então entra
        {
            if (fila[pai][1] < fila[child][1]) /* Se o pai já for menor então o acervo já está ordenado */
            {
                break;
            }
            troca_posicoes(posicao[fila[pai][0]], posicao[fila[child][0]]);
            troca_fila(fila[pai], fila[child]);
            pai = child;
        }
        else
        {
            if (fila[pai][1] < fila[child + 1][1])
            {
                break;
            }
            troca_posicoes(posicao[fila[pai][0]], posicao[fila[child + 1][0]]);
            troca_fila(fila[pai], fila[child + 1]);
            pai = child + 1;
        }
    }
}

/**
 * @brief Troca o primeiro nó(nó com maior prioridade) do acervo com o ultimo, organiza o acervo e retorna o elemento com maior prioridade
 *
 * @return int: elemento com maior prioridade
 */
int Proximo_na_fila()
{
    Free--;
    troca_fila(fila[0], fila[Free]);
    posicao[fila[0][0]] = posicao[fila[Free][0]];
    posicao[fila[Free][0]] = -1;
    FixDown(); /* ao trocar o primeiro com o ultimo elemento da fila, esta função reorganiza a fila de forma a respeitar as prioridades */
    return fila[Free][0];
}

/**
 * @brief A função liberta todo o espaço alocado na fila
 *
 *
 \return void
 */
void freefila()
{
    for (int i = 0; i < tamanho; i++)
    {
        free(fila[i]);
    }
    free(fila);
    free(posicao);
}
