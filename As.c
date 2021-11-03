/*bibliotecas do projeto*/
#include "As.h"
#include "Funcoes_aux.h"
#include "Ficheiros_dados.h"
/*bibliotecas do projeto*/
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/** \brief identifica o tipo da célula indicada
 * \param int **maze: array de duas dimensões que contém o labirinto
 * \param int l: linha da peça que está a ser testada
 * \param int c: coluna da peça que está a ser testada
 * \param int lin: total de linhas do labirinto
 * \param int col: total de colunas do labirinto
 *
 * \return int: número do tipo da peça das cordenadas (l,c)
 *
 */
int FA1(int **maze, int l, int c, int lin, int col)
{
    int A1 = out(l, c, lin, col);
    if (A1 != -2)
    {
        A1 = maze[l][c];
    }
    return A1;
}

/** \brief indica se algum vizinho da célula indicada é uma célula branca
 * \param int **maze: array de duas dimensões que contém o labirinto
 * \param int l: linha da peça que está a ser testada
 * \param int c: coluna da peça que está a ser testada
 * \param int lin: total de linhas do labirinto
 * \param int col: total de colunas do labirinto
 *
 * \return int: confirmação ou não da existência de um vizinho célula branca da celula de coordenadas (l,c)
 *
 */
int FA2(int **maze, int l, int c, int lin, int col)
{
    /*verificação se a célula não está fora do tabuleiro*/
    if ((out(l, c, lin, col) == -2))
        return -2;
    /*verificação do tipo das células vizinhas e se estas cumprem a condição de ser branca*/
    if ((out(l + 1, c, lin, col) != -2 && maze[l + 1][c] == 0) || (out(l, c + 1, lin, col) != -2 && maze[l][c + 1] == 0) || (out(l - 1, c, lin, col) != -2 && maze[l - 1][c] == 0) || (out(l, c - 1, lin, col) != -2 && maze[l][c - 1] == 0))
    {
        return 1;
    }
    return 0;
}

/** \brief indica se algum vizinho da célula indicada é uma célula cizenta
 * \param int **maze: array de duas dimensões que contém o labirinto
 * \param int l: linha da peça que está a ser testada
 * \param int c: coluna da peça que está a ser testada
 * \param int lin: total de linhas do labirinto
 * \param int col: total de colunas do labirinto
 *
 * \return int:  confirmação ou não da existência de um vizinho célula cizento da celula de coordenadas (l,c)
 *
 */
int FA3(int **maze, int l, int c, int lin, int col)
{ /*verificação se a célula não está fora do tabuleiro*/
    if ((out(l, c, lin, col) == -2))
        return -2;
    /*verificação do tipo das células vizinhas e se estas cumprem a condição de ser cizenta*/
    if ((out(l + 1, c, lin, col) != -2 && maze[l + 1][c] >= 1) || (out(l, c + 1, lin, col) != -2 && maze[l][c + 1] >= 1) || (out(l - 1, c, lin, col) != -2 && maze[l - 1][c] >= 1) || (out(l, c - 1, lin, col) != -2 && maze[l][c - 1] >= 1))
    {
        return 1;
    }
    return 0;
}

/** \brief indica se algum vizinho da célula indicada é uma célula preta
 * \param int **maze: array de duas dimensões que contém o labirinto
 * \param int l: linha da peça que está a ser testada
 * \param int c: coluna da peça que está a ser testada
 * \param int lin: total de linhas do labirinto
 * \param int col: total de colunas do labirinto
 *
 * \return int:  confirmação ou não da existência de um vizinho célula preta da celula de coordenadas (l,c)
 *
 */
int FA4(int **maze, int l, int c, int lin, int col)
{ /*verificação se a célula não está fora do tabuleiro*/
    if ((out(l, c, lin, col) == -2))
        return -2;
    /*verificação do tipo das células vizinhas e se estas cumprem a condição de ser preta*/
    if ((out(l + 1, c, lin, col) != -2 && maze[l + 1][c] == -1) || (out(l, c + 1, lin, col) != -2 && maze[l][c + 1] == -1) || (out(l - 1, c, lin, col) != -2 && maze[l - 1][c] == -1) || (out(l, c - 1, lin, col) != -2 && maze[l][c - 1] == -1))
    {
        return 1;
    }
    return 0;
}

/** \brief indica se a célula de dada pelas coordenadas (l,c) é quebrável
 * \param int **maze: array de duas dimensões que contém o labirinto
 * \param int l: linha da peça que está a ser testada
 * \param int c: coluna da peça que está a ser testada
 * \param int lin: total de linhas do labirinto
 * \param int col: total de colunas do labirinto
 *
 * \return int:  afirma ou nega a possibilidade de quebrar a celula de coordenadas (l,c)
 *
 */
int FA5(int **maze, int l, int c, int lin, int col)
{
    if (out(l, c, lin, col) == -2)
        return -2;
    else if (maze[l][c] <= 0)
        return -1;
    /*analiza se as duas células vizinhas na vertical ou na horizontal são brancas*/
    else if ((out(l - 1, c, lin, col) != -2) && (out(l + 1, c, lin, col) != -2) && maze[l - 1][c] == 0 && maze[l + 1][c] == 0)
    {
        return 1;
    }
    else if ((out(l, c + 1, lin, col) != -2) && (out(l, c - 1, lin, col) != -2) && maze[l][c - 1] == 0 && maze[l][c + 1] == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/** \brief indica se a célula de coordenadas (l,c) e a célula de coordenadas (l2,c2) pertencem à mesma sala
 * \param int **maze: array de duas dimensões que contém o labirinto
 * \param int l: linha da peça que está a ser testada
 * \param int c: coluna da peça que está a ser testada
 * \param int lin: total de linhas do labirinto
 * \param int col: total de colunas do labirinto
 *
 * \return int: devolve -2 se alguma das células estiver do labirinto fora, 1 se estiverem na mesma sala e 0 se isso não acontecer
 */
int FA6(int **maze, int l, int c, int lin, int col, int l2, int c2, int total_salas)
{ /*Baseado no compressed weighted quick union algorithm*/
    int i = 0, j = 0, x = 0, t = 0;
    int *id = (int *)malloc((lin + 1) * (col + 1) * sizeof(int));
    int *sz = (int *)malloc((lin + 1) * (col + 1) * sizeof(int));
    // Inicialização das variáveis
    for (i = 0; i < ((lin + 1) * (col + 1)); i++)
    {
        sz[i] = 1;

        if (maze[i / (lin + 1)][i % (lin + 1)] != 0) // tirar no final do projeto, apenas para ajudar a visualizar!!!
        {
            id[i] = -1;
        }
        else
        {
            id[i] = i;
        }
    }
    // Percorre a matriz toda para conectar horizontalmente as peças
    for (int p = 0; p <= lin; p++)
    {
        for (int q = 0; q <= col - 1; q++)
        { // Vê se as duas coordenadas são células brancas para poder conectar
            if (maze[p][q] == 0 && maze[p][q + 1] == 0)
            { // Percorre o i e o j até chegar ao nó
                for (i = p * (col + 1) + q; i != id[i]; i = id[i])
                    ;
                for (j = p * (col + 1) + q + 1; j != id[j]; j = id[j])
                    ;

                if (i == j)
                    continue;
                if (sz[i] < sz[j]) /*escolhe qual é o menor para facilitar a união*/
                {
                    id[i] = j;
                    sz[j] += sz[i];
                    t = j;
                }
                else
                {
                    id[j] = i;
                    sz[i] += sz[j];
                    t = i;
                }
                total_salas--;
                for (i = p * (col + 1) + q; i != id[i]; i = x)
                {
                    x = id[i];
                    id[i] = t;
                }
                for (j = p * (col + 1) + q + 1; j != id[j]; j = x)
                {
                    x = id[j];
                    id[j] = t;
                }
            }
        }
    }
    // Percorre a matriz toda para conectar verticalmente as peças
    for (int p = 0; p <= lin - 1; p++)
    {
        for (int q = 0; q <= col; q++)
        {
            if (maze[p][q] == 0 && maze[p + 1][q] == 0)
            {
                for (i = p * (col + 1) + q; i != id[i]; i = id[i])
                    ;
                for (j = (p + 1) * (col + 1) + q; j != id[j]; j = id[j])
                    ;
                if (i == j)
                    continue;
                if (sz[i] < sz[j]) /*escolhe qual é o menor para facilitar a união*/
                {
                    id[i] = j;
                    sz[j] += sz[i];
                    t = j;
                }
                else
                {
                    id[j] = i;
                    sz[i] += sz[j];
                    t = i;
                }
                total_salas--;
                for (i = p * (col + 1) + q; i != id[i]; i = x)
                {
                    x = id[i];
                    id[i] = t;
                }
                for (j = (p + 1) * (col + 1) + q; j != id[j]; j = x)
                {
                    x = id[j];
                    id[j] = t;
                }
            }
        }
    }
    for (int p = 0; p <= lin; p++)
    {
        for (int q = 0; q <= col; q++)
        {
            printf("%3d ", maze[p][q]); //"%2d ", id[p * (col + 1) + q]
        }
        printf("\n");
    }

    for (int p = 0; p <= lin; p++)
    {
        for (int q = 0; q <= col; q++)
        {
            if (maze[p][q] == 0)
            {
                for (i = p * (col + 1) + q; i != id[i]; i = id[i])
                    ;
                maze[p][q] = -i - 3;
            }
        }
    }
    printf("\n\n");

    for (int p = 0; p <= lin; p++)
    {
        for (int q = 0; q <= col; q++)
        {
            printf("%3d ", maze[p][q]); // p * (col + 1) + q
        }
        printf("\n");
    }
    printf("\n%d\n", total_salas);
    // Percorre o i e o j até chegar ao nó e se no final forem iguais quer dizer que estão na mesma sala
    for (i = (l * (col + 1)) + c; i != id[i]; i = id[i])
        ;
    for (j = (l2 * (col + 1)) + c2; j != id[j]; j = id[j])
        ;
    if (i == j)
    {
        free(id);
        free(sz);
        return 1; /*as duas células estão na mesma sala*/
    }
    else
    {
        free(id);
        free(sz);
        return 0; /*as duas células estão em salas diferentes*/
    }
}