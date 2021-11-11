/*bibliotecas do projeto*/
#include "As.h"
#include "Funcoes_aux.h"
#include "Ficheiros_dados.h"
#include "Grafo.h"
/*bibliotecas do C*/
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief escolhe com base na leitura do ficheiro qual dos modos A's usar
 *
 * @param maze: array de duas dimensões que contém o labirinto
 * @param l: linha da peça que está a ser testada
 * @param c: coluna da peça que está a ser testada
 * @param lin: total de linhas do labirinto
 * @param col: total de colunas do labirinto
 * @param modo: String que contêm o modo de jogo
 * @param l2: linha da segunda peça do modo A6
 * @param c2: coluna da segunda peça do modo A6
 * @param total_salas: Número total de salas existentes
 *
 * @return int: resposta ao problema
 */
int mod(int **maze, int l, int c, int lin, int col, char *modo, int l2, int c2, int total_salas)
{
    int resp;
    if ((strcmp(modo, "A1")) == 0)
    { /*Se a string modo é A1 então chama A1 e as seguintes são semelhantes*/
        resp = FA1(maze, l, c, lin, col);
        return resp;
    }
    else if ((strcmp(modo, "A2")) == 0)
    {
        resp = FA2(maze, l, c, lin, col);
        return resp;
    }
    else if ((strcmp(modo, "A3")) == 0)
    {
        resp = FA3(maze, l, c, lin, col);
        return resp;
    }
    else if ((strcmp(modo, "A4")) == 0)
    {
        resp = FA4(maze, l, c, lin, col);
        return resp;
    }
    else if ((strcmp(modo, "A5")) == 0)
    {
        resp = FA5(maze, l, c, lin, col);
        if (resp > 0)
        {
            resp = 1;
        }
        return resp;
    }
    else if ((strcmp(modo, "A6")) == 0)
    {
        if ((out(l, c, lin, col) == -2) || (out(l2, c2, lin, col) == -2))
        { /*verifica se as coordenadas indicadas não estão fora do tabuleiro*/
            return -2;
        }
        if (maze[l][c] != 0 || maze[l2][c2] != 0)
        { /*verifica se alguma das coordenadas indicadas não é brancas*/
            return 0;
        }
        resp = FA6(maze, l, c, lin, col, l2, c2, &(total_salas));
        return resp;
    }
    else
    {
        exit(0);
    }
}

/**
 * @brief liberta todo o espaço alocado para a tabela que constitui o labirinto
 *
 * @param maze: Array de duas dimensões que contém o labirinto
 * @param lin: numero de linhas máximas do tabuleiro
 *
 * @return void
 */
void freetabela(int **maze, int lin)
{
    for (int i = 0; i < lin; i++)
    {
        free(maze[i]);
    }
    free(maze);
}

/** \brief
 * \param int l
 * \param int c
 * \param int lin
 * \param int col
 *
 * \return int
 *
 */

/**
 * @brief verifica se a peça dada nas coordenadas (l,c) está dentro do tabuleiro
 *
 * @param l: linha da peça que está a ser testada
 * @param c: coluna da peça que está a ser testada
 * @param lin: total de linhas do labirinto
 * @param col: total de colunas do labirinto
 * @return int: retorna -2 se a célula estiver fora do tabuleiro e 0 se não
 */
int out(int l, int c, int lin, int col)
{
    if (l < 0 || l > lin || c < 0 || c > col)
        return -2;
    return 0;
}

/** \brief A função procura por "." numa string e "troca" o último "." por um " "
 * \param char *str: string em que queremos procurar os "."
 *
 * \return void
 *
 */
void separar(char *str)
{
    int i;
    char *ptroca = NULL;
    for (i = 0; str[i] != '\0'; i++) /*Executa enquanto não chegar ao final da string*/
    {
        if (str[i] == '.')
        {
            ptroca = &str[i];
        }
    }
    *ptroca = ' ';
}

/** \brief fecha o ficheiro de entrada e de saída
 * \param FILE *fmaze: ficheiro de entrada com os dados
 * \param FILE *fsol: ficheiro de saida com a solução
 *
 * \return void
 *
 */
void fechar(FILE *fmaze, FILE *fsol)
{
    fclose(fmaze);
    fclose(fsol);
}

/**
 * @brief Procura a aresta mais barata que junta pares de salas
 *
 * @param maze: array de duas dimensões que contém o labirinto
 * @param lin: total de linhas do mapa
 * @param col: total de colunas do mapa
 * @param vertices: total de nós do grafo
 * @param g: estrutura do grafo que contem a lista dos nós e os vertices
 */
void aresta_barata(int **maze, int lin, int col, int vertices, G *g)
{
    int k = 0, a = 0, b = 0;
    ladj *aux;
    short p;
    for (p = 0; p <= lin; p++)
    {
        for (short q = 0; q <= col; q++)
        {
            if ((k = FA5(maze, p, q, lin, col)) > 0) /*1- parte horizontalmente; 2- parte verticalmente; 3- parte nas duas direções*/
            {
                if (k == 1 || k == 3) /*é quebrável na horizontal*/
                {

                    a = -(maze[p - 1][q]) - 3; /* O valor do maze é negado pois ao "pintar" as salas com tags foram usados valores negativos a começar no -3 pois estes nao interferem com nenhuma outra implementação e agora é revertido */
                    b = -(maze[p + 1][q]) - 3;
                    if (a == b) // Se a parede estiver a separar a mesma sala ignora-se
                    {
                        continue;
                    }
                    aux = adjacente(maze[p][q], b, g->list[a], p + 1, q + 1);
                    if (aux == NULL)
                    {
                        continue;
                    }
                    g->list[a] = aux;
                    g->list[b] = adjacente(maze[p][q], a, g->list[b], p + 1, q + 1);
                }
                if (k == 2 || k == 3) /*é quebrável na vertival*/
                {
                    a = -(maze[p][q - 1]) - 3;
                    b = -(maze[p][q + 1]) - 3;
                    if (a == b)
                    {
                        continue;
                    }
                    aux = adjacente(maze[p][q], b, g->list[a], p + 1, q + 1);
                    if (aux == NULL)
                    {
                        continue;
                    }
                    g->list[a] = aux;
                    g->list[b] = adjacente(maze[p][q], a, g->list[b], p + 1, q + 1);
                }
            }
        }
        if (p >= 2) /* Como só se usa a linha de cima e de baixo para a verifação,
        então as linhas podem ser libertadas à medida que deixam de ser uteis */
        {
            free(maze[p - 2]);
        }
    }
    if (lin != 0)
    {
        free(maze[p - 2]);
    }
    free(maze[p - 1]);
    free(maze);
}
