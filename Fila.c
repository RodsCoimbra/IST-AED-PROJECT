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

void Filaini(int vertices)
{
    fila = (ladj *)calloc(1, vertices * sizeof(ladj));
    tamanho = vertices;
    Free = 0;
}

void Filainsert(ladj novo)
{
    if ((Free + 1) < tamanho)
    {
        fila[Free] = novo;
        Fixup(novo, Free, fila);
        Free++;
    }
}

void Fixup(ladj novo, int livre, ladj *queue)
{
    for (ladj aux; livre > 0 && queue[(livre - 1) / 2].custo > queue[livre].custo; livre = (livre - 1) / 2)
    {
        aux = queue[livre];
        queue[livre] = queue[(livre - 1) / 2];
        queue[(livre - 1) / 2] = aux;
    }
}

/*void FixDown(ladj queue[], int Free)
{
    int N = Free-1;
    fdp = (pairetirado-1)*2;
    if(queue[(livre - 1) / 2].custo > queue[livre].custo){

    }

}*/
