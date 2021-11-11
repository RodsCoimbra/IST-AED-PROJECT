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

#define troca_posicoes(a, b) \
    {                        \
        int aux;             \
        aux = a;             \
        a = b;               \
        b = aux;             \
    }
int Vazia()
{
    if (Free == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
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
    fila = (int *)malloc(vertices * sizeof(int));
    posicao = (int *)malloc(vertices * sizeof(int));
    if (fila == NULL || posicao == NULL)
    {
        exit(0);
    }
    for (int i = 0; i < vertices; i++)
    {
        fila[i] = 0;
        posicao[i] = -1;
    }
    tamanho = vertices;
    Free = 0; /*Total de nós no grafo existentes */
}

/**
 * @brief
 *
 * @param no: Nó do grafo que se quer inserir
 * @param custo: Custo do nó que se quer inserir
 *
 \return void
 */
void Filainsert(int no, int custo, int *pesos)
{
    if (((Free + 1) < tamanho))
    {
        fila[Free] = no;
        Fixup(Free, pesos);
        Free++;
    }
}

int Comparar(int a, int b, int *pesos)
{
    if (pesos[a] > pesos[b])
    {
        return 0; /*  O Pai é maior O FILHO SOBE*/
    }
    else if (pesos[a] < pesos[b])
    {
        return 1; /* O filho é maior */
    }
    else
    {
        return 69;
    }
}
/**
 * @brief Com o nó passado como argumento, a função eleva-o até este estar na posição correta do acervo segundo a ordem de prioridades
 *
 * @param Free: número total de nós na fila
 *
 \return void
 */
void Fixup(int Free, int *pesos)
{
    while (Free > 0 && Comparar(fila[(Free - 1) / 2], fila[Free], pesos))
    {
        troca_posicoes(fila[Free], fila[(Free - 1) / 2]);
        Free = (Free - 1) / 2;
    }
}

/**
 * @brief A função verifica se o primeiro elemento está bem posicionado e se não acontecer fá-lo descer na fila até à posição correta do acervo, respeitando a ordem de prioridades
 *
 *
 \return void
 */
void FixDown(int Free, int N, int *pesos)
{
    int Child; /* índice de um nó descendente */
    while (2 * Free < N - 1)
    { /* enquanto não chegar às folhas */
        Child = 2 * Free + 1;
        /* Selecciona o maior descendente.
*/
        /* Nota: se índice Child é N-1, então só há um descendente */
        if (Child < (N - 1) && Comparar(fila[Child], fila[Child + 1], pesos))
            Child++;
        if (!Comparar(fila[Free], fila[Child], pesos))
            break; /* condição acervo */
        /* satisfeita
*/
        troca_posicoes(fila[Free], fila[Child]);
        /* continua a descer a árvore */
        Free = Child;
    }
}

/**
 * @brief Troca o primeiro nó(nó com maior prioridade) do acervo com o ultimo, organiza o acervo e retorna o elemento com maior prioridade
 *
 * @return int: elemento com maior prioridade
 */
int Proximo_na_fila(int *pesos) /* aka delmax/delmin */
{
    /* troca maior elemento com último da tabela e reordena com FixDown */
    troca_posicoes(fila[0], fila[Free - 1]);
    FixDown(0, Free - 1, pesos);
    /* ultimo elemento não considerado na reordenação */
    return fila[--Free];
}

/**
 * @brief A função liberta todo o espaço alocado na fila
 *
 *
 \return void
 */
void freefila()
{

    free(fila);
    free(posicao);
}
