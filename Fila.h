#ifndef Fila_h
#define Fila_h
#include "Grafo.h"
int **fila;
int *posicao;
int tamanho;
int Free;

void Filaini(int vertices);
void Filainsert(int no, int custo);
void Fixup(int Free);
void FixDown();
int Proximo_na_fila();
void freefila();
#endif