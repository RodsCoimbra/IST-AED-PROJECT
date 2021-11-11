#ifndef Fila_h
#define Fila_h
#include "Grafo.h"

int **Filaini(int vertices, int *posicao, int *tamanho);
void Filainsert(int no, int custo, int **fila, int *posicao, int *Free);
void Fixup(int Free, int **fila, int *posicao);
void FixDown(int **fila, int *posicao, int Free);
int Proximo_na_fila(int **fila, int *posicao, int *Free);
void freefila(int **fila, int *posicao, int *tamanho);
#endif