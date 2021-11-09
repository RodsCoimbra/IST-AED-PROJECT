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
    if (fila == NULL)
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
        tamanho = vertices;
        Free = 0;
        fila[i][0] = -1;
        fila[i][1] = 0;
    }
}
int expoente(int a, int b)
{
    int aux = 1;
    for (int i = 0; i < b; i++)
    {
        aux *= a;
    }
    return aux;
}
void Filainsert(int no, int custo, int comparacao_custo)
{
    static int la = 0;
    int i = 0, j, k, flag = 1;
    for (j = 0; i < Free && fila[i][0] != no && flag == 1; j++)
    {
        printf("Entrei..  %d", ++la);
        for (i = expoente(2, i - 1), flag = 0, k = expoente(2, i); i < k && i < Free && fila[i][0] != no; i++)
        {
            if (fila[i][1] <= comparacao_custo)
            {
                flag = 1;
            }
        }
    }
    if (fila[i][0] == no)
    {
        // printf("k %d %d  ", ++k, fila[i][0]);
        fila[i][1] = custo;
        Fixup(i);
    }
    else
    {
        if ((Free + 1) <= tamanho)
        {
            // printf("j %d %d  ", ++k, fila[i][0]);
            fila[Free][0] = no;
            fila[Free][1] = custo;
            Fixup(Free);
            Free++;
        }
        else
        {
            printf("excedeu :))");
            exit(0);
        }
    }
    printf("\n\nsai\n\n");
    /*for (int i = 0; i < 7; i++)
    {
        printf("%d:%d  ", fila[i][0], fila[i][1]);
    }
    printf("Free %d\n", Free);*/
}
void Fixup(int livre)
{
    for (int *aux; livre > 0 && fila[(livre - 1) / 2][1] > fila[livre][1]; livre = (livre - 1) / 2)
    {
        aux = fila[livre];
        fila[livre] = fila[(livre - 1) / 2];
        fila[(livre - 1) / 2] = aux;
    }
}

void FixDown()
{
    int N = Free - 1, child, idx = 0;
    int *aux;
    // printf("\nFree:%d\n", Free);
    while ((idx * 2) < N)
    {
        // printf("idx*2->%d N->%d\n", (idx * 2), (N));
        child = (idx * 2) + 1;
        aux = fila[idx];
        if (child == N || fila[child][1] < fila[child + 1][1])
        {
            if (fila[idx][1] < fila[child][1])
            {
                break;
            }
            fila[idx] = fila[child];
            fila[child] = aux;
            idx = child;
        }
        else
        {
            if (fila[idx][1] < fila[child + 1][1])
            {
                break;
            }
            fila[idx] = fila[child + 1];
            fila[child + 1] = aux;
            idx = child + 1;
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
}