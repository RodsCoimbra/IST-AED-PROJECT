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

/** \brief Lê o ficheiro de entrada, cria os tabuleiros e devolve as respostas no ficheiro de saida
 * \param FILE *fmaze: ficheiro de entrada com os dados
 * \param FILE *fsol: ficheiro de saida com a solução
 *
 * \return void
 */
void Labirinto_fase1(FILE *fmaze, FILE *fsol)
{
    int lin = 0, col = 0, parede, l = 0, c = 0, linaux = -2, colaux = -1, l2 = 0, c2 = 0, resposta;
    int total_salas = 0;
    short matriz_alocada = 0;
    char modo[3];
    int **maze = NULL; // labirinto e matriz das arestas mais baratas
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
        total_salas = lin * col;
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
        total_salas -= parede;
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

void Labirinto_fase2(FILE *fmaze, FILE *fsol)
{
    int lin = 0, col = 0, parede, l = 0, c = 0, linaux = -2, colaux = -1;
    int total_salas = 0;
    short matriz_alocada = 0, flag = 0;
    int **maze = NULL;
    int sala_tesouro = 0;
    G *g;
    while (1)
    {
        if (fscanf(fmaze, "%d %d %d %d", &lin, &col, &l, &c) != 4)
        {
            if (feof(fmaze) != 0)
                break;
            else
            {
                fechar(fmaze, fsol);
            }
        }
        if (flag)
        {
            fprintf(fsol, "\n\n");
        }
        else
        {
            flag = 1;
        }
        if (fscanf(fmaze, "%d", &parede) != 1)
        {
            fechar(fmaze, fsol);
        }
        if (parede == 0)
        {
            fprintf(fsol, "0\n");
            continue;
        }
        if (out(l - 1, c - 1, lin - 1, col - 1) == -2 || (l == 1 && c == 1))
        {
            for (int i = 0, l1, c1, custo; i < parede; i++)
            {
                if (fscanf(fmaze, "%d %d %d", &l1, &c1, &custo) != 3)
                {
                    fechar(fmaze, fsol);
                }
            }
            if ((l == 1 && c == 1))
            {
                fprintf(fsol, "0\n");
            }
            else
            {
                fprintf(fsol, "-1\n");
            }

            continue;
        }
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
        if (FA1(maze, l - 1, c - 1, lin - 1, col - 1) != 0)
        {
            fprintf(fsol, "-1\n");
            continue;
        }
        if (FA6(maze, l - 1, c - 1, lin - 1, col - 1, 0, 0, &total_salas))
        {
            fprintf(fsol, "0\n");
            continue;
        }
        ////////////////////////////Meter resposta aqui
        g = Grafoini(total_salas);
        if (g == NULL)
        {
            freetabela(maze, lin);
            fechar(fmaze, fsol);
            exit(0);
        }
        aresta_barata(maze, lin - 1, col - 1, g->V, g);
        sala_tesouro = -(maze[l - 1][c - 1] + 3);
        matriz_alocada = 0;
        freetabela(maze, lin);
        linaux = -2;
        colaux = -1;
        if (g->list[sala_tesouro] == NULL)
        {
            fprintf(fsol, "-1\n");
            continue;
        }
        encontra_caminho(g, sala_tesouro, fsol);
        Grafofree(g);
        ////////////////////////////////////////////////
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
void open_files(FILE **fmaze, FILE **fsol, char *fileread, char *filewrite, int fase)
{
    if ((*fmaze = fopen(fileread, "r")) == NULL)
    {
        free(filewrite);
        free(fileread);
        exit(0);
    }
    separar(fileread);
    sscanf(fileread, " %s", filewrite);
    if (fase == 1)
    {
        strcat(filewrite, ".sol2"); // MUDAR PARA .sol e mudar o tamanho do vetor no main.c
    }
    else
    {
        strcat(filewrite, ".sol1"); // MUDAR PARA .sol1
    }
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