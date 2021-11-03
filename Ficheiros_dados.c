/*bibliotecas do projeto*/
#include "As.h"
#include "Funcoes_aux.h"
#include "Ficheiros_dados.h"
/*bibliotecas*/
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/** \brief Lê o ficheiro de entrada, cria os tabuleiros e devolve as respostas no ficheiro de saida
 * \param FILE *fmaze: ficheiro de entrada com os dados
 * \param FILE *fsol: ficheiro de saida com a solução
 *
 * \return void
 */
void Labirinto(FILE *fmaze, FILE *fsol)
{
    int lin = 0, col = 0, parede, l = 0, c = 0, linaux = -2, colaux = -1, l2 = 0, c2 = 0, resposta;
    int total_salas = 0;
    short matriz_alocada = 0;
    char modo[3];
    int **maze = NULL;
    while (1)
    {
        if (fscanf(fmaze, "%d %d %d %d %s", &lin, &col, &l, &c, modo) != 5)
        {
            if (feof(fmaze) != 0)
                break;
            else
            {
                fechar(fmaze, fsol);
            }
        }
        total_salas = lin*col;
        if ((strcmp(modo, "A6")) != 0)
        {
            if (fscanf(fmaze, "%d", &parede) != 1)
            {
                fechar(fmaze, fsol);
            }
        }
        else
        {
            if (fscanf(fmaze, "%d %d %d", &l2, &c2, &parede) != 3)
            {
                fechar(fmaze, fsol);
            }
        }
        total_salas-=parede;
        if (out(l - 1, c - 1, lin - 1, col - 1) == -2 || (((strcmp(modo, "A6")) == 0) && (out(l2 - 1, c2 - 1, lin - 1, col - 1) == -2)))
        {
            for (int i = 0, l1, c1, custo; i < parede; i++)
            {
                if (fscanf(fmaze, "%d %d %d", &l1, &c1, &custo) != 3)
                {
                    fechar(fmaze, fsol);
                }
            }
            fprintf(fsol, "-2\n\n");
        }
        else
        {
            matriz_alocada = 1;
            if (lin != linaux)
            {
                if (linaux != -2)
                {
                    freetabela(maze, linaux);
                }
                linaux = lin;
                colaux = -1;
                maze = (int **)malloc(lin * sizeof(int *));
                if (maze == NULL)
                {
                    exit(0);
                }
            }
            if (col != colaux)
            {
                if (colaux != -1)
                {
                    for (int i = 0; i < lin; i++)
                    {
                        free(maze[i]);
                    }
                }
                for (int i = 0; i < lin; i++)
                {
                    maze[i] = (int *)calloc(1, col * sizeof(int));
                    if (maze[i] == NULL)
                    {
                        exit(0);
                    }
                }
                colaux = col;
            }
            else
            {
                for (int i = 0; i < lin; i++)
                {
                    for (int j = 0; j < col; j++)
                    {
                        maze[i][j] = 0;
                    }
                }
            }
            for (int i = 0, l1, c1, custo; i < parede; i++)
            {
                if (fscanf(fmaze, "%d %d %d", &l1, &c1, &custo) != 3)
                {
                    fechar(fmaze, fsol);
                }
                maze[l1 - 1][c1 - 1] = custo;
            }
            resposta = mod(maze, l - 1, c - 1, lin - 1, col - 1, modo, l2 - 1, c2 - 1, total_salas);
            fprintf(fsol, "%d\n\n", resposta);
        }
    }
    if (matriz_alocada == 1)
        freetabela(maze, lin);
    fechar(fmaze, fsol);
}

/** \brief Lê o ficheiro de entrada, cria os tabuleiros e devolve as respostas no ficheiro de saida
 * \param FILE **fmaze: ficheiro de entrada com os dados
 * \param FILE **fsol: ficheiro de saida com a solução
 * \param char *fileread: string com o nome do ficheiro de entrada (.in1)
 * \param char *filewrite: string com o nome do ficheiro de saida (.sol1)
 * \return void
 */
void open_files(FILE **fmaze, FILE **fsol, char *fileread, char *filewrite)
{
    if ((*fmaze = fopen(fileread, "r")) == NULL)
    {
        free(filewrite);
        free(fileread);
        exit(0);
    }
    separar(fileread);
    sscanf(fileread, " %s", filewrite);
    strcat(filewrite, ".sol2");
    if ((*fsol = fopen(filewrite, "w")) == NULL)
    { // Se der erro ao abrir o ficheiro de saida, então o ficheiro de leitura fecha
        free(filewrite);
        free(fileread);
        fclose(*fmaze);
        exit(0);
    }
    free(filewrite);
    free(fileread);
}