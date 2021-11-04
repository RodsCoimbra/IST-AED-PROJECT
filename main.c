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
    short fase = 0; // 1 se for projeto final, 0 se for 1ª fase do projeto
    FILE *fmaze = NULL, *fsol = NULL;
    char *fileread = NULL, *filewrite = NULL;
    opt = getopt(argc, argv, "s:"); // recebe os argumentos de entrada ao iniciar o programa
    switch (opt)
    {
    case 's':
        tamanho = strlen(argv[2]) + 1;
        fileread = (char *)calloc(1, tamanho * sizeof(char)), filewrite = (char *)calloc(1, (tamanho + 1) * sizeof(char)); // alocação do array que conterá o nome dos ficheiros de leitura e de escrita
        if (fileread == NULL || filewrite == NULL)                                                                         // verifica se a alocação de memória foi bem sucedida
        {
            exit(0);
        }
        sscanf(optarg, " %s", fileread);
        // confirma que o ficheiro de leitura tem extensão in1
        if (fileread[tamanho - 5] != '.' || fileread[tamanho - 4] != 'i' || fileread[tamanho - 3] != 'n' || fileread[tamanho - 2] != '1')
        {
            free(fileread);
            free(filewrite);
            exit(0);
        }
        break;
    default:
    {
        fase = 1;
        tamanho = strlen(argv[1]) + 1;
        fileread = (char *)calloc(1, tamanho * sizeof(char)), filewrite = (char *)calloc(1, (tamanho + 2) * sizeof(char)); // alocação do array que conterá o nome dos ficheiros de leitura e de escrita
        if (fileread == NULL || filewrite == NULL)                                                                         // verifica se a alocação de memória foi bem sucedida
        {
            exit(0);
        }
        sscanf(argv[1], " %s", fileread);
        // confirma que o ficheiro de leitura tem extensão in
        if (fileread[tamanho - 4] != '.' || fileread[tamanho - 3] != 'i' || fileread[tamanho - 2] != 'n')
        {
            free(fileread);
            free(filewrite);
            exit(0);
        }
        break;
    }
    }
    open_files(&fmaze, &fsol, fileread, filewrite, fase);
    if (fase == 1) // Se for ficheiros do projeto final
    {
        Labirinto_fase2(fmaze, fsol);
    }
    else // Se for ficheiros do projeto intermedio
    {
        Labirinto_fase1(fmaze, fsol);
    }
}