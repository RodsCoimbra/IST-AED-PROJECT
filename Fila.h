#ifndef Fila_h
#define Fila_h
#include "Grafo.h"
ladj *fila;
int tamanho;
int Free;

void Filaini(int vertices);
void Filainsert(ladj novo);
void Fixup(ladj novo, int Fila, ladj *fila);
#endif