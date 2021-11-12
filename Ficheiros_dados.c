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

/**
 * @brief Lê o ficheiro de entrada, cria os tabuleiros e devolve as respostas no ficheiro de saida para a 1ª fase do projeto
 *
 * @param fmaze: ficheiro de entrada com os dados
 * @param fsol: ficheiro de saida com a solução
 *
 * @return void
 */
void Labirinto_fase1(FILE *fmaze, FILE *fsol)
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
        if ((strcmp(modo, "A6")) != 0) // caso não seja o modo A6 lê de uma forma, senão lê de outra
        {
            if (fscanf(fmaze, "%d", &parede) != 1)
            {
                fechar(fmaze, fsol);
                exit(0);
            }
        }
        else
        {
            if (fscanf(fmaze, "%d %d %d", &l2, &c2, &parede) != 3)
            {
                fechar(fmaze, fsol);
                exit(0);
            }
        }
        if (out(l - 1, c - 1, lin - 1, col - 1) == -2 || (((strcmp(modo, "A6")) == 0) && (out(l2 - 1, c2 - 1, lin - 1, col - 1) == -2))) // Se algumas das coordenadas está fora do tabuleiro
        {
            for (int i = 0, l1, c1, custo; i < parede; i++) // Passar as paredes, mas sem armazenar nada
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
            matriz_alocada = 1; // Flag que diz se a matriz foi alocada
            if (lin != linaux)  // Caso a matriz já tenha sido alocada com a mesma quantidade de linhas evita de dar free e outro malloc
            {
                if (linaux != -2) // Caso em que as linhas são diferente e não é a primeira matriz a ser alocada
                {
                    freetabela(maze, linaux);
                }
                linaux = lin;
                colaux = -1; // Como foi dado free da tabela toda então a matriz tem de ser de novo alocada e portanto mete-se esta flag a -1 para dizer isso
                maze = (int **)malloc(lin * sizeof(int *));
                if (maze == NULL)
                {
                    exit(0);
                }
            }
            if (col != colaux) // Caso a matriz já tenha sido alocada com a mesma quantidade de colunas evita de dar free e outro malloc
            {
                if (colaux != -1) // Caso em que é diferente as colunas e não é a primeira matriz a ser alocada ou a matriz já foi free por causa das linhas diferentes
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
            else // caso a matriz seja de tamanho exatamente igual ele simplesmente passa a matriz toda a 0
            {
                for (int i = 0; i < lin; i++)
                {
                    for (int j = 0; j < col; j++)
                    {
                        maze[i][j] = 0;
                    }
                }
            }
            for (int i = 0, l1, c1, custo; i < parede; i++) // ler as paredes
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
    if (matriz_alocada == 1) // se tiver uma matriz alocada, então libertá-la
        freetabela(maze, lin);
    fechar(fmaze, fsol);
}
/**
 * @brief Lê o ficheiro de entrada, cria os tabuleiros e devolve as respostas no ficheiro de saida para a fase final do projeto
 *
 * @param fmaze: ficheiro de entrada com os dados
 * @param fsol: ficheiro de saida com a solução
 *
 * @return void
 */
void Labirinto_fase2(FILE *fmaze, FILE *fsol)
{
    int lin = 0, col = 0, parede, l = 0, c = 0;
    int total_salas = 0;
    short matriz_alocada = 0, flag = 0;
    int **maze = NULL;
    int sala_tesouro = 0;
    G *g;
    while (1)
    {
        if (matriz_alocada == 1)
        {
            freetabela(maze, lin);
            matriz_alocada = 0;
        }

        if (fscanf(fmaze, "%d %d %d %d", &lin, &col, &l, &c) != 4)
        {
            if (feof(fmaze) != 0)
                break;
            else
            {
                fechar(fmaze, fsol);
                exit(0);
            }
        }
        if (flag) // Apenas para as respostas darem com os mesmos parágrafos dos testes na página da cadeira
        {
            fprintf(fsol, "\n\n");
        }
        else
        {
            flag = 1; // Apenas para as respostas darem com os mesmos parágrafos dos testes na página da cadeira
        }
        if (fscanf(fmaze, "%d", &parede) != 1)
        {
            fechar(fmaze, fsol);
            exit(0);
        }
        if (parede == 0 && (out(l - 1, c - 1, lin - 1, col - 1) != -2)) // Se não houver parede e o local do tesourofor dentro do tabuleiro
        {
            fprintf(fsol, "0\n");
            continue;
        }
        if ((out(l - 1, c - 1, lin - 1, col - 1) == -2) || (l == 1 && c == 1))
        {
            for (int i = 0, l1, c1, custo; i < parede; i++) // apenas para passar as paredes do labirinto atual(sem armazenar)
            {
                if (fscanf(fmaze, "%d %d %d", &l1, &c1, &custo) != 3)
                {
                    fechar(fmaze, fsol);
                    exit(0);
                }
            }
            if ((l == 1 && c == 1)) // caso o tesouro esteja nas coordenadas 1,1
            {
                fprintf(fsol, "0\n");
            }
            else // caso em que o tesouro está fora do tabuleiro
            {
                fprintf(fsol, "-1\n");
            }

            continue;
        }

        maze = (int **)malloc(lin * sizeof(int *));
        if (maze == NULL)
        {
            exit(0);
        }

        for (int i = 0; i < lin; i++)
        {
            maze[i] = (int *)calloc(1, col * sizeof(int));
            if (maze[i] == NULL)
            {
                exit(0);
            }
        }

        matriz_alocada = 1;                             // Flag que diz se a matriz foi alocada
        for (int i = 0, l1, c1, custo; i < parede; i++) // ler as paredes
        {
            if (fscanf(fmaze, "%d %d %d", &l1, &c1, &custo) != 3)
            {
                fechar(fmaze, fsol);
                exit(0);
            }
            maze[l1 - 1][c1 - 1] = custo;
        }
        if (FA1(maze, l - 1, c - 1, lin - 1, col - 1) != 0) // se a célula do tesouro não for branca
        {
            fprintf(fsol, "-1\n");
            continue;
        }
        if (FA6(maze, l - 1, c - 1, lin - 1, col - 1, 0, 0, &total_salas)) // se a célula do tesouro estiver na mesma sala
        {
            fprintf(fsol, "0\n");
            continue;
        }
        g = Grafoini(total_salas);
        if (g == NULL)
        {
            freetabela(maze, lin);
            fechar(fmaze, fsol);
            exit(0);
        }
        /////////////////////////////////RETirar
        /* for (int p = 0; p < 20; p++)
        {
            for (int q = 0; q < 40; q++)
                if (maze[p][q] != -1 && maze[p][q] < 0)
                {
                    fprintf(fsol, "%4d ", -(maze[p][q]) - 3); //"%2d ", id[p * (col + 1) + q]
                }
                else
                {
                    if (maze[p][q] == -1)
                    {
                        fprintf(fsol, "%4d ", maze[p][q]);
                    }
                    else
                    {
                        fprintf(fsol, "%4d ", -(maze[p][q]) - 1);
                    }
                }
            fprintf(fsol, "\n");
        }
        fprintf(fsol, "\n\n\n"); */
        //////////////////////
        sala_tesouro = -(maze[l - 1][c - 1] + 3);
        aresta_barata(maze, lin - 1, col - 1, g->V, g, fsol);
        ///////////////////////////////////
        // printf("\n\n");
        /* ladj *aux;
        for (int i = 0; i < g->V; i++)
        {
            if (g->list[i] != NULL)
            {
                fprintf(fsol, "%2d->  ", i);
                for (aux = g->list[i]; aux != NULL; aux = aux->next)
                {
                    fprintf(fsol, "%d:%d ", aux->no, aux->custo);
                }
                fprintf(fsol, "-1\n");
            }
        }
        fprintf(fsol, "\n\n\n"); */
        ////////////////////////////////////
        matriz_alocada = 0;                // retira a flag de matriz alocada visto que esta foi libertada na função aresta_barata
        if (g->list[sala_tesouro] == NULL) // Se a sala do tesouro não tiver nenhuma sala que consiga chegar
        {
            fprintf(fsol, "-1\n");
            Grafofree(g);
            continue;
        }
        encontra_caminho(g, sala_tesouro, fsol);
        Grafofree(g);
    }
    if (matriz_alocada == 1) // se tiver uma matriz alocada, então libertá-la
        freetabela(maze, lin);
    fechar(fmaze, fsol);
}

/**
 * @brief Lê o ficheiro de entrada, cria os tabuleiros e devolve as respostas no ficheiro de saida
 *
 * @param fmaze: ficheiro de entrada com os dados
 * @param fsol: ficheiro de saida com a solução
 * @param fileread: string com o nome do ficheiro de entrada (.in1 ou .in)
 * @param filewrite: string com o nome do ficheiro de saida (.sol1 ou .sol)
 * @param fase: 0 se for a 1ª fase do projeto e 1 se for a fase final
 *
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
    separar(fileread); // separa o ficheiro da sua extensão
    sscanf(fileread, " %s", filewrite);
    if (fase == 1)
    {
        strcat(filewrite, ".so2");
    }
    else
    {
        strcat(filewrite, ".sol1");
    }
    if ((*fsol = fopen(filewrite, "w")) == NULL)
    {
        free(filewrite);
        free(fileread);
        fclose(*fmaze);
        exit(0);
    }
    free(filewrite);
    free(fileread);
}