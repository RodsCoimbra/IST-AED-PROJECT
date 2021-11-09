#ifndef Fila_h
#define Fila_h
#include "Grafo.h"
int **fila;
int tamanho;
int Free;
int expoente(int a, int b);
void Filaini(int vertices);
void Filainsert(int no, int custo, int comparacao_custo);
void Fixup(int livre);
void FixDown();
int Proximo_na_fila();
void freefila();
#endif