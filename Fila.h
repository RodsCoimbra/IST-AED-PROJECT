#ifndef Fila_h
#define Fila_h
#include "Grafo.h"
int *fila;
int *posicao;
int tamanho;
int Free;

void Filaini(int vertices);
void Filainsert(int no, int custo, int *pesos);
void Fixup(int Free, int *pesos);
void FixDown(int Free, int N, int *pesos);
int Proximo_na_fila(int *pesos);
void freefila();
#endif