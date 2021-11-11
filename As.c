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
 * \return int: retorna 1 se for quebrável na horizontal, 2 é quebrável na vertical e 3 é quebrável em ambas.
 *
 */
int FA5(int **maze, int l, int c, int lin, int col)
{
    int direcao = 0;
    if (out(l, c, lin, col) == -2)
        return -2;
    else if (maze[l][c] == 0 || maze[l][c] == -1)
        return -1;
    /*analiza se as duas células vizinhas na vertical ou na horizontal são brancas*/
    if ((out(l - 1, c, lin, col) != -2) && (out(l + 1, c, lin, col) != -2) && maze[l - 1][c] < -2 && maze[l + 1][c] < -2)
    {
        direcao++; // 1 significa é quebrável na horizontal
    }
    if ((out(l, c + 1, lin, col) != -2) && (out(l, c - 1, lin, col) != -2) && maze[l][c - 1] < -2 && maze[l][c + 1] < -2)
    {
        direcao += 2; // 2 significa é quebrável na vertical
    }
    return direcao; // 3 significa é quebrável em ambas as direcoes
}

/** \brief
 * \param int **maze
 * \param int l: linha da peça que está a ser testada
 * \param int c: coluna da peça que está a ser testada
 *
 * \return int: devolve 1 se as células estiverem na mesma sala e 0 se isso não acontecer
 */

/**
 * @brief indica se a célula de coordenadas (l,c) e a célula de coordenadas (l2,c2) pertencem à mesma sala e "pinta" as salas
 *
 * @param maze: array de duas dimensões que contém o labirinto
 * @param l: linha da célula que está a ser testada
 * @param c: coluna da célula que está a ser testada
 * @param lin: total de linhas do labirinto
 * @param col: total de colunas do labirinto
 * @param l2: linha da segunda célula a ser testada
 * @param c2: coluna da segunda célula a ser testada
 * @param total_salas: total de salas do labirinto
 *
 * @return int: retorna 1 se as células pertencerem à mesma sala, 0 caso contrário
 */
int FA6(int **maze, int l, int c, int lin, int col, int l2, int c2, int *total_salas)
{ /*Baseado no compressed weighted quick union algorithm*/
    int i = 0, j = 0, x = 0, t = 0, k, m, f, h;
    int *sz = (int *)malloc((lin + 1) * (col + 1) * sizeof(int));
    if (sz == NULL)
    {
        exit(0);
    }

    // Inicialização das variáveis
    for (int p = 0; p <= lin; p++)
    {
        for (int q = 0; q <= col; q++)
        {
            sz[p * (col + 1) + q] = 1;
            if (maze[p][q] > 0) // Se forem paredes quebráveis
            {
                maze[p][q] = -(maze[p][q]) - 1; // faz o simétrico das paredes e retira 1 para distinguir as paredes inquebráveis
            }
            else if (maze[p][q] == 0) // Se forem célula branca
            {
                maze[p][q] = p * (col + 1) + q;
            }
        }
    }
    // Percorre a matriz toda para conectar horizontalmente as peças
    for (int p = 0; p <= lin; p++)
    {
        for (int q = 0; q <= col - 1; q++)
        { // Vê se as duas coordenadas são células brancas para poder conectar
            if (maze[p][q] >= 0 && maze[p][q + 1] >= 0)
            { // Percorre o i e o j até chegar ao nó
                for (i = p * (col + 1) + q, f = p, h = q; i != maze[f][h]; i = maze[f][h], f = i / (col + 1), h = i % (col + 1))
                    ;
                for (j = p * (col + 1) + q + 1, k = p, m = q + 1; j != maze[k][m]; j = maze[k][m], k = j / (col + 1), m = j % (col + 1))
                    ;
                if (i == j)
                    continue;
                if (sz[i] < sz[j]) /*escolhe qual é o menor para facilitar a união*/
                {
                    maze[f][h] = j;
                    sz[j] += sz[i];
                    t = j;
                }
                else
                {
                    maze[k][m] = i;
                    sz[i] += sz[j];
                    t = i;
                }
                for (i = p * (col + 1) + q, f = p, h = q; i != maze[f][h]; i = x, f = i / (col + 1), h = i % (col + 1))
                {
                    x = maze[f][h];
                    maze[f][h] = t;
                }
                for (j = p * (col + 1) + q + 1, k = p, m = q + 1; j != maze[k][m]; j = x, k = j / (col + 1), m = j % (col + 1))
                {
                    x = maze[k][m];
                    maze[k][m] = t;
                }
            }
        }
    }
    // Percorre a matriz toda para conectar verticalmente as peças
    for (int p = 0; p <= lin - 1; p++)
    {
        for (int q = 0; q <= col; q++)
        {
            if (maze[p][q] >= 0 && maze[p + 1][q] >= 0)
            {
                for (i = p * (col + 1) + q, f = p, h = q; i != maze[f][h]; i = maze[f][h], f = i / (col + 1), h = i % (col + 1))
                    ;
                for (j = (p + 1) * (col + 1) + q, k = p + 1, m = q; j != maze[k][m]; j = maze[k][m], k = j / (col + 1), m = j % (col + 1))
                    ;
                if (i == j)
                    continue;
                if (sz[i] < sz[j]) /*escolhe qual é o menor para facilitar a união*/
                {
                    maze[f][h] = j;
                    sz[j] += sz[i];
                    t = j;
                }
                else
                {
                    maze[k][m] = i;
                    sz[i] += sz[j];
                    t = i;
                }
                for (i = p * (col + 1) + q, f = p, h = q; i != maze[f][h]; i = x, f = i / (col + 1), h = i % (col + 1))
                {
                    x = maze[f][h];
                    maze[f][h] = t;
                }
                for (j = (p + 1) * (col + 1) + q, k = p + 1, m = q; j != maze[k][m]; j = x, k = j / (col + 1), m = j % (col + 1))
                {
                    x = maze[k][m];
                    maze[k][m] = t;
                }
            }
        }
    }

    for (int p = 0; p <= lin; p++)
    {
        for (int q = 0; q <= col; q++)
        {
            if (maze[p][q] < 0)
            {
                sz[p * (col + 1) + q] = maze[p][q]; // passar as paredes para o size para as ir buscar depois
            }
        }
    }

    *(total_salas) = -3; // começa em -3 porque > 0 são paredes, -1 parede inquebrável e -2 fora do maze
    for (int p = 0; p <= lin; p++)
    {
        for (int q = 0; q <= col; q++)
        {
            if (maze[p][q] >= 0) // Se for branca
            {
                for (i = p * (col + 1) + q, f = p, h = q; maze[f][h] >= 0 && i != maze[f][h]; i = maze[f][h], f = i / (col + 1), h = i % (col + 1))
                    ;
                if (maze[f][h] >= 0) // Caso em que ainda nenhuma célula daquela sala está pintada na conectividade e portanto cria
                {
                    maze[f][h] = *(total_salas); // Pinta as salas a começar em -3 e vai descendo
                    *(total_salas) -= 1;
                }
                maze[p][q] = maze[f][h];
            }
            else
            {
                if (sz[p * (col + 1) + q] < 0) // Caso seja uma das paredes passadas anteriormente para o size
                {
                    if (sz[p * (col + 1) + q] == -1) // Se for parede inquebrável(-1) basta colocar -1 no maze[p][q]
                    {
                        maze[p][q] = sz[p * (col + 1) + q];
                    }
                    else
                    {
                        maze[p][q] = -(sz[p * (col + 1) + q]) - 1; // Se for parede quebrável faz o simétrico de
                                                                   // volta e substrai - 1 para voltar ao valor original da parede
                    }
                }
            }
        }
    }
    *(total_salas) = (-*(total_salas)-3);
    //  Percorre o i e o j até chegar ao nó e se no final forem iguais quer dizer que estão na mesma sala
    i = maze[l][c];
    j = maze[l2][c2];
    free(sz);
    if (i == j)
    {
        return 1; /*as duas células estão na mesma sala*/
    }
    else
    {
        return 0; /*as duas células estão em salas diferentes*/
    }
}