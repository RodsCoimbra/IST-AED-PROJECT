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
        Free = 0;
    }
}
void Filainsert(int no, int custo)
{
    if (posicao[no] == -1)
    {
        fila[Free][0] = no;
        fila[Free][1] = custo;
        posicao[no] = Free;
        Fixup(Free);
        Free++;
    }
    else
    {
        fila[posicao[no]][1] = custo;
        Fixup(posicao[no]);
    }
}

void Fixup(int Free)
{
    for (int *aux, aux2, livre = Free; livre > 0 && fila[(livre - 1) / 2][1] > fila[livre][1]; livre = (livre - 1) / 2)
    {
        aux = fila[livre];
        fila[livre] = fila[(livre - 1) / 2];
        fila[(livre - 1) / 2] = aux;
        aux2 = posicao[fila[livre][0]];
        posicao[fila[livre][0]] = posicao[fila[(livre - 1) / 2][0]];
        posicao[fila[(livre - 1) / 2][0]] = aux2;
    }
}

void FixDown()
{
    int N = Free - 1, child, pai = 0;
    int *aux, aux2;
    while ((pai * 2) < N)
    {
        child = (pai * 2) + 1;
        aux = fila[pai];
        aux2 = posicao[fila[pai][0]];
        if (child == N || fila[child][1] < fila[child + 1][1])
        {
            if (fila[pai][1] < fila[child][1])
            {
                break;
            }
            posicao[fila[pai][0]] = posicao[fila[child][0]];
            posicao[fila[child][0]] = aux2;
            fila[pai] = fila[child];
            fila[child] = aux;
            pai = child;
        }
        else
        {
            if (fila[pai][1] < fila[child + 1][1])
            {
                break;
            }
            posicao[fila[pai][0]] = posicao[fila[child + 1][0]];
            posicao[fila[child + 1][0]] = aux2;
            fila[pai] = fila[child + 1];
            fila[child + 1] = aux;
            pai = child + 1;
        }
    }
}

int Proximo_na_fila()
{
    int *aux;
    Free--;
    aux = fila[0];
    fila[0] = fila[Free];
    fila[Free] = aux;
    posicao[fila[0][0]] = posicao[fila[Free][0]];
    posicao[fila[Free][0]] = -1;
    FixDown();
    return fila[Free][0];
}

void freefila()
{
    for (int i = 0; i < tamanho; i++)
    {
        free(fila[i]);
    }
    free(fila);
    free(posicao);
}
