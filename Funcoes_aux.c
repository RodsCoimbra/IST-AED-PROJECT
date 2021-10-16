/*bibliotecas do projeto*/
#include "As.h"
#include "Funcoes_aux.h"
#include "Ficheiros_dados.h"
/*bibliotecas do C*/
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int mod(int **maze, int l, int c, int lin, int col, char *modo, int l2, int c2)
{ /*escolhe com base na leitura do ficheiro qual da sfunções A chamar*/
    int resp;
    if ((strcmp(modo, "A1")) == 0)
    { /*Lê A1 então chama A1 e as seguintes são semelhantes*/
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
        return resp;
    }
    else if ((strcmp(modo, "A6")) == 0)
    {
        if ((out(l, c, lin, col) == -2) || (out(l2, c2, lin, col) == -2))
        { /*virifica se as coordenadas indicadas não estão fora do tabuleiro*/
            return -2;
        }
        if (maze[l][c] != 0 || maze[l2][c2] != 0)
        { /*virifica se as coordenadas indicadas são brancas*/
            return 0;
        }
        resp = FA6(maze, l, c, lin, col, l2, c2);
        return resp;
    }
    else
    {
        exit(0);
    }
}

void freetabela(int **maze, int lin)
{ /*liberta todo o espaço alocado para a tabela que constitui o labirinto*/
    for (int i = 0; i < lin; i++)
    {
        free(maze[i]);
    }
    free(maze);
}

int out(int l, int c, int lin, int col)
{ /*retorna -2 se a célula estiver fora do tabuleiro*/
    if (l < 0 || l > lin || c < 0 || c > col)
        return -2;
    return 0;
}

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

void fechar(FILE *fmaze, FILE *fsol)
{ /*fecha o ficheiro de entrada e de saída*/
    fclose(fmaze);
    fclose(fsol);
}