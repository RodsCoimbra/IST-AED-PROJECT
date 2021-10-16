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
{   /*verificação se a célula não está fora do tabuleiro*/
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
{   /*verificação se a célula não está fora do tabuleiro*/
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
int FA6(int **maze, int l, int c, int lin, int col, int l2, int c2)
{ /*para duas células de entrada a função indica se pertencem à mesma sala do labirinto*/
    /*Baseado no weighted quick union algorithm*/
    int i = 0, j = 0;
    int *id = (int *)malloc((lin + 1) * (col + 1) * sizeof(int));
    int *sz = (int *)malloc((lin + 1) * (col + 1) * sizeof(int));
    for (i = 0; i < ((lin + 1) * (col + 1)); i++)
    {
        sz[i] = 1;
        if ((*(*(maze + i / (col + 1)) + i % (col + 1))) > 0 || (*(*(maze + i / (col + 1)) + i % (col + 1))) == -1)
        {
            id[i] = -1;
        }

        id[i] = i;
    }
    
    for (int p = 0; p <= lin; p++)
    {
        for (int q = 0; q <= col - 1; q++)
        {
            i = p * (col + 1) + q;
            j = p * (col + 1) + q + 1;
            if (maze[p][q] == 0 && p > 0 && maze[p - 1][q] == 0)
            {
                id[i] = id[(p - 1) * (col + 1) + q];
            }
            if (maze[p][q + 1] == 0 && p > 0 && maze[p - 1][q + 1] == 0)
            {
                id[j] = id[(p - 1) * (col + 1) + q + 1];
            }
            if (maze[p][q] == 0 && maze[p][q + 1] == 0)
            {
                for (; i != id[i]; i = id[i])
                    ;
                for (; j != id[j]; j = id[j])
                    ;

                if (i == j)
                    continue;
                if (sz[i] < sz[j])
                {
                    id[i] = j;
                    sz[j] += sz[i];
                }
                else
                {
                    id[j] = i;
                    sz[i] += sz[j];
                }
            }
        }
    }
    for (i = (l * (col + 1)) + c; i != id[i]; i = id[i])
        ;
    for (j = (l2 * (col + 1)) + c2; j != id[j]; j = id[j])
        ;
    if (i == j)
    {
        free(id);
        free(sz);
        return 1;
    }
    else
    {
        free(id);
        free(sz);
        return 0;
    }
}