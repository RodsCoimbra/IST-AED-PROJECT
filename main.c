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

int main(int argc, char *argv[])
{
    opterr = 0;
    int opt, tamanho = 0;
    FILE *fmaze = NULL, *fsol = NULL;
    tamanho = strlen(argv[2]) + 1;                                                                                            /*tamanho */
    char *fileread = (char *)calloc(1, tamanho * sizeof(char)), *filewrite = (char *)calloc(1, (tamanho + 1) * sizeof(char)); /*alocação do array para ler e para escrever nos ficheiros*/
    if (fileread == NULL || filewrite == NULL)                                                                                /*verifica se a alocação de memória foi bem sucedida*/
    {
        exit(0);
    }
    while ((opt = getopt(argc, argv, "s:")) != -1)
    { /*recebe os argumentos de entrada ao iniciar o programa*/
        switch (opt)
        {
        case 's':
            sscanf(optarg, " %s", fileread);
            if (fileread[tamanho - 5] != '.' || fileread[tamanho - 4] != 'i' || fileread[tamanho - 3] != 'n' || fileread[tamanho - 2] != '1')
            {
                exit(0);
            }
            break;
        default:
        {
            exit(0);
        }
        }
    }
    open_files(&fmaze, &fsol, fileread, filewrite);
    Labirinto(fmaze, fsol);
}