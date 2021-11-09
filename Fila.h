#ifndef Fila_h
#define Fila_h
#include "Grafo.h"
int **fila;
int tamanho;
int Free;
int expoente(int a, int b);
void Filaini(int vertices);
void Filainsert(int no, int custo, int *pertence_a_fila);
void Fixup(int livre, int *pertence_a_fila);
void FixDown();
int Proximo_na_fila();
void freefila();
void MudarPrioridade(int pertence_a_fila, int custo);
#endif